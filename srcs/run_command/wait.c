#include "minishell.h"

static int	ft_wait(t_list **process, t_config *config)
{
	int		stat_loc;
	pid_t	pid;

	config->last_exit = 0;
	while (1)
	{
		stat_loc = 0;
		pid = waitpid(-1, &stat_loc, WNOHANG);
		if (pid < 0 || config->shell_state == SIGINT_COMMAND)
		{
			ft_free_all_process(process, 1);
			config->last_exit = 1;
			return (0);
		}
		else if (!pid && config->shell_state == SIGTSTP_COMMAND
			&& (config->shell_state = RUNNING_COMMAND))
			return (1);
		else if (WIFSTOPPED(stat_loc))
			return (1);
		else if (pid && WIFEXITED(stat_loc))
		{
			ft_free_one_process(process, pid);
			config->last_exit |= WEXITSTATUS(stat_loc);
		}
		else if (pid && WIFSIGNALED(stat_loc))
		{
			ft_printsignal(WTERMSIG(stat_loc), pid, process);
			ft_free_all_process(process, 1);
			config->last_exit = 1;
			return (0);
		}
		if (!(*process))
			return (0);
	}
}

void		ft_wait_sentence(t_list *job, t_config *config)
{
	t_list	*new;

	if (!(config->fg_sentence)
		|| (!(new = ft_lstnew((void*)config->fg_sentence, SENT))
		&& ft_freegiveone((void **)&config->fg_sentence)))
		ft_error(SHNAME, "parser", "malloc error on process control", CR_ERROR);
	else if (config->fg_sentence && !(config->fg_sentence = NULL))
		ft_list_push_front(&job, new);
	if (ft_wait(&job, config))
	{
		if (!(new = ft_lstnew((void*)job, JOB)))
		{
			ft_error(SHNAME, "parser", "malloc error on job control", CR_ERROR);
			ft_free_all_process(&job, 1);
		}
		else
			ft_list_push_front(&(config->jobs), new);
	}
}

static char	*ft_build_sshell_sentence(t_list *begin, t_config *config)
{
	char	*tmp;
	char	*tocpy;
	char	*memo;

	memo = config->fg_sentence;
	config->fg_sentence = NULL;
	if (!(ft_build_sentence(begin, config)))
		return (NULL);
	tmp = config->fg_sentence;
	config->fg_sentence = memo;
	if (!(tocpy = ft_strnew(ft_strlen(tmp) + 4))
		&& ft_freegiveone((void**)&tmp))
		return (NULL);
	ft_strcpy(tocpy, "( ");
	ft_strcpy(tocpy + 2, tmp);
	ft_strcat(tocpy, " )");
	ft_freegiveone((void**)&tmp);
	return (tocpy);
}

int			ft_build_sentence(t_list *begin, t_config *config)
{
	char	*tmp;
	char	*tocpy;

	while (begin)
	{
		tocpy = NULL;
		if (!begin->data_size)
			tocpy = ft_strtabchrjoin((char **)begin->data, ' ');
		else if (begin->data_size == SSHELL)
			tocpy = ft_build_sshell_sentence(begin->data, config);
		else
			tocpy = ft_strdup((char *)begin->data);
		if (!tocpy && ft_freegiveone((void**)&config->fg_sentence))
			return (0);
		if (config->fg_sentence)
			tmp = ft_strchrjoin(config->fg_sentence, ' ', tocpy);
		else
			tmp = ft_strdup(tocpy);
		ft_freegiveone((void **)&config->fg_sentence);
		ft_freegiveone((void **)&tocpy);
		config->fg_sentence = tmp;
		begin = begin->next;
	}
	return (1);
}
