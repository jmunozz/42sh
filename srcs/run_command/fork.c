/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2016/04/29 12:21:42 by tboos            ###   ########.fr       */
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
		ft_error(SHNAME, "fork fail for", command, CR_ERROR | SERROR);
	else if (father == 0)
	{
		ft_signal_reset();
		execve(command, argv, env);
	}
	else
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
		ft_error(SHNAME, "SORRY", JEDI_ERR, CR_ERROR);
	exit(0);
}
