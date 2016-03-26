#include "minishell.h"

void		ft_fewef(char *command, char **argv, char **env)
{
	pid_t		father;
	int			stat_loc;

	stat_loc = 0;
	if (-1 > (father = fork()))
		ft_fork_error();
	else if (father == 0)
		execve(command, argv, env);
	else if (father !=  0)
		waitpid(father, &stat_loc, 0);
}

void		ft_kill_father(t_config *config)
{
	ft_free_config(config);
	if(-1 == kill(getppid(), SIGKILL))
		ft_putstr_fd("SORRY, I couldn't kill my father, he's a jedi", 2);
	exit(0);
}

void		ft_usr_exit(void)
{
	pid_t	child_id;
	int		status;

	status = 0;
	while (1)
	{
		if ((child_id = fork()) == -1)
			ft_fork_error();
		else if (child_id == 0)
			return ;
		else
			waitpid(child_id, &status, 0);
	}
}
