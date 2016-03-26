#include "minishell.h"

void		ft_fewef(char *command, char **argv, char **env)
{
	pid_t		father;
	int			stat_loc;
	char		buf[3];

	stat_loc = 0;
	if (-1 > (father = fork()))
		ft_fork_error();
	else if (father == 0)
	{
		if (SIG_ERR == signal(SIGINT, SIG_IGN)
			|| SIG_ERR == signal(SIGTSTP, SIG_IGN))
			ft_putstr_fd("WARNING : won't be able to send signal", 2);
		execve(command, argv, env);
	}
	while (father !=  0)
	{
		ft_bzero(buf, 3);
//		if (read(0, buf, 2) && !ft_strcmp(buf, "^C"))
//			kill(father, SIGKILL);
//		else if (!ft_strcmp(buf, "^Z")
		if (waitpid(father, &stat_loc, WNOHANG) > 0)
			break;
	}
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
