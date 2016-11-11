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

void		ft_wait_sentence(t_list *job, char *sentence, t_config *config)
{
	t_list	*new;

	if (sentence && !(new = ft_lstnew((void*)sentence, SENT))
			&& ft_freegiveone((void **)&sentence))
		ft_error(SHNAME, "parser", "malloc error on process control", CR_ERROR);
	else if (sentence)
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
