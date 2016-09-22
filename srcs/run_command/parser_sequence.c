#include "minishell.h"

static int		*ft_close_pipe(int *new, int *old)
{
	if (old)
	{
		close(old[0]);
		close(old[1]);
	}
	if (new)
		return (new);
	return (NULL);
}

static void		ft_pipe_process(t_list *begin, t_config *config, int *r_pipe)
{
	if (r_pipe)
	{
		dup2(r_pipe[0], STDIN_FILENO);
		close(r_pipe[0]);
		close(r_pipe[1]);
	}
	if (begin->next && begin->next->data_size == PIPE)
	{
		dup2(((int *)(begin->next->data))[1], STDOUT_FILENO);
		close(((int *)(begin->next->data))[0]);
		close(((int *)(begin->next->data))[1]);
	}
	ft_signal_reset();
	ft_launch_process(begin, config);
	exit(0);
}

static t_list	*ft_fork_process(t_list *begin, t_config *config, int *r_pipe)
{
	t_list	*new;
	pid_t	pid;

	if (ft_is_no_fork_builtin(((char**)(begin->data))[0]))
	{
		ft_launch_process(begin, config);
		return (NULL);
	}
	else if ((pid = fork()) == -1)
	{
		ft_error(SHNAME, "parser", "fork error", CR_ERROR);
		return (NULL);
	}
	else if (!pid)
		ft_pipe_process(begin, config, r_pipe);
	else if (!(new = ft_lstnew((void *)&pid, PROS)))
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
		if (!begin->data_size)
		{
			if ((tmp = ft_fork_process(begin, config, r_pipe)))
				ft_list_push_back(&process, tmp);
		}
		else if (begin->data_size == PIPE)
			r_pipe = ft_close_pipe((int*)(begin->data), r_pipe);
		begin = begin->next;
	}
	ft_close_pipe(NULL, r_pipe);
	return (process);
}
