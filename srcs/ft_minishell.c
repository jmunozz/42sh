/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:06:19 by rbaran            #+#    #+#             */
/*   Updated: 2016/06/01 17:56:21 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_checkcmd(char *cmdline, t_conf *config)
{
	char		**cmdline_split;
	static void	(*tabf[5])(t_conf *, char **) = {&ft_cd, &ft_exit,
		&ft_unsetenv, &ft_env, &ft_setenv};
	int			builtin;
	t_bin		*cmd;

	cmd = NULL;
	if (!cmdline || !*cmdline || !(cmdline_split = ft_strsplit(cmdline, ' ')))
		return ;
	if ((builtin = ft_findbuiltin(*cmdline_split)) != -1)
		(tabf[builtin])(config, cmdline_split);
	else if (*cmdline_split[0] == '/' ||
			*cmdline_split[0] == '.' ||
			(cmd = ft_findcmd(*cmdline_split, ft_hashsearch(config,
															*cmdline_split))))
		ft_execcmd(cmd, cmdline_split, config);
	else
		ft_error(*cmdline_split, CMD_NOTFOUND, KEEP);
	ft_free_split(cmdline_split);
	free(cmdline_split);
}

static void	ft_splitcmd(t_conf *config, char *cmdline)
{
	char	**split;
	char	**splitbuf;

	if ((split = ft_strsplit(cmdline, ';')))
	{
		splitbuf = split;
		while (split && *split)
		{
			ft_checkcmd(*split, config);
			split++;
		}
		ft_free_split(splitbuf);
		free(splitbuf);
	}
}

void		ft_minishell(t_conf *config)
{
	char	*cmdline;

	ft_printprompt();
	cmdline = NULL;
	while (1)
	{
		cmdline = ft_scaninput(config);
		ft_splitcmd(config, cmdline);
		if (cmdline)
		{
			ft_lst_push_front(&(config->begin_history), cmdline,
								ft_strlen(cmdline) + 1);
			config->history = config->begin_history;
			free(cmdline);
			cmdline = NULL;
		}
		ft_printprompt();
	}
}
