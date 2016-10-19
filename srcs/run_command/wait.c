#include "minishell.h"

int		ft_wait(t_list **process)
{
	int		stat_loc;
	pid_t	pid;

	while (1)
	{
		stat_loc = 0;
		if ((pid = waitpid(-1, &stat_loc, 0)) > 0)
		{
			if (WIFSTOPPED(stat_loc))
				return (1);
			if (WIFEXITED(stat_loc))
				ft_free_one_process(process, pid);
			if (!(*process))
				return (0);
		}
	}
}

void	ft_wait_sentence(t_list *job, char *sentence, t_config *config)
{
	t_list	*new;

	if (sentence && !(new = ft_lstnew((void*)sentence, SENT)))
		ft_error(SHNAME, "parser", "malloc error on process control", CR_ERROR);
	else if (sentence)
		ft_list_push_front(&job, new);
	if (ft_wait(&job))
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
