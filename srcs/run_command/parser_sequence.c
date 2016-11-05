#include "minishell.h"

static int		*ft_close_pipe(int *new, int *old)
{
	if (old)
	{
		close(old[0]);
		close(old[1]);
		free(old);
	}
	if (new)
		return (new);
	return (NULL);
}

static void		ft_pipe_process(t_list *begin, t_config *config, int *r_pipe)
{
	if (r_pipe)
	{
dprintf(1, "on dup2 et read\n");
		dup2(r_pipe[0], STDIN_FILENO);
		close(r_pipe[0]);
		close(r_pipe[1]);
	}
	if (begin->next && begin->next->data_size == PIPE)
	{
dprintf(1, "on dup2 et write\n");
		dup2(((int *)(begin->next->data))[1], STDOUT_FILENO);
		close(((int *)(begin->next->data))[0]);
		close(((int *)(begin->next->data))[1]);
	}
	ft_signal_reset();
	if (begin->data_size == SSHELL && (config->shell_state = RUNNING_SSHELL))
	{
		if ((config->last_exit = ft_strtabifindstart(config->env, "SHLVL")) != -1)
			ft_setenv("SHLVL",
				ft_st_itoa(ft_atoi(config->env[config->last_exit] + 6) - 1),
			config);
		ft_parse((t_list*)begin->data, config);
	}
	else
		ft_launch_process(begin, config);
	ft_status(config->shell_state == RUNNING_SSHELL ? config->last_exit : 1);
	ft_shell_exit(config, NULL);
}

static t_list	*ft_fork_process(t_list *begin, t_config *config, int *r_pipe)
{
	t_list	*new;
	pid_t	pid;
	pid_t	*mem;

	new = NULL;
	if (!begin->data_size && !ft_quote_handle(begin, config))
	{
		ft_error(SHNAME, "parser", "malloc error handling quote", CR_ERROR);
		return (NULL);
	}
	if (!begin->data_size && ft_is_no_fork_builtin(((char**)(begin->data))[0]))
		ft_launch_process(begin, config);
	else if ((pid = fork()) == -1)
	{
		ft_error(SHNAME, "parser", "fork error", CR_ERROR);
		return (NULL);
	}
	else if (!pid)
		ft_pipe_process(begin, config, r_pipe);
	else if (!(mem = (pid_t*)ft_memalloc(sizeof(pid_t))) || !(*mem = pid)
		|| !(new = ft_lstnew((void *)mem, PROS)))
		ft_error(SHNAME, "parser", "malloc error on process control", CR_ERROR);
	return (new);
}

 t_list		*ft_run_sentence(t_list *begin, t_config *config, int *r_pipe)
{
	t_list	*tmp;
	t_list	*process;

	process = NULL;
	while (begin)
	{
		if (!begin->data_size || begin->data_size == SSHELL)
		{
			if ((tmp = ft_fork_process(begin, config, r_pipe)))
				ft_list_push_back(&process, tmp);
		}
		else if (begin->data_size == PIPE)
		{
			r_pipe = ft_close_pipe((int*)(begin->data), r_pipe);
			if (!ft_build_pipe(begin->next, config, &r_pipe))
				return (process);
		}
		begin = begin->next;
	}
	ft_close_pipe(NULL, r_pipe);
	return (process);
}
