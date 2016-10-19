/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 10:41:48 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 15:43:18 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

void		ft_execcmd(t_bin *cmd, char **cmdline_split, t_conf *config)
{
	char	*fullpath;
	pid_t	father;
	int		stat_loc;

	fullpath = cmd ? ft_strjoin(cmd->path, cmd->name) : *cmdline_split;
	if ((cmd && !(ft_access(fullpath, FILES))) || !ft_access(fullpath, FILES))
	{
		if (cmd)
			free(fullpath);
		return ;
	}
	if ((father = fork()) == -1)
		return ;
	if (father == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(fullpath, cmdline_split, config->env);
		signal(SIGINT, SIG_IGN);
		exit(1);
	}
	else
		waitpid(father, &stat_loc, 0);
	if (cmd)
		free(fullpath);
}
