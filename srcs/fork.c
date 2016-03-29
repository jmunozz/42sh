/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 19:22:25 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ft_putstr_fd("WARNING : won't be able to send signal\n", 2);
		execve(command, argv, env);
	}
	while (father != 0)
	{
		ft_bzero(buf, 3);
		if (waitpid(father, &stat_loc, WNOHANG) > 0)
			break ;
	}
}

void		ft_kill_father(t_config *config)
{
	ft_free_config(config);
	if (-1 == kill(getppid(), SIGKILL))
		ft_putstr_fd("SORRY, I couldn't kill my father, he's a jedi\n", 2);
	exit(0);
}
