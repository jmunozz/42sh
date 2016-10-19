/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 12:29:17 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/30 16:19:05 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_returnpath(t_conf *config, char *cmd)
{
	char	**parsenv;
	char	*path;

	parsenv = NULL;
	path = NULL;
	if (!cmd)
		if ((parsenv = ft_parseenv(config->env, "HOME")))
			path = ft_strdup(parsenv[1]);
	if (cmd[0] == '~')
		if ((parsenv = ft_parseenv(config->env, "HOME")))
			path = ft_strjoin(parsenv[1], (cmd + 1));
	if (cmd[0] == '-')
		if ((parsenv = ft_parseenv(config->env, "OLDPWD")))
			path = ft_strjoin(parsenv[1], (cmd + 1));
	if (!path && cmd)
		path = ft_strdup(cmd);
	if (parsenv)
	{
		ft_free_split(parsenv);
		free(parsenv);
	}
	return (path);
}

static void	ft_modifypwd(t_conf *config, char *var)
{
	char	**parsenv;
	char	*send[4];
	char	buf[256];

	send[3] = NULL;
	if ((parsenv = ft_parseenv(config->env, var)))
	{
		send[0] = "setenv";
		send[1] = var;
		send[2] = getcwd(buf, 256);
		ft_setenv(config, send);
		ft_free_split(parsenv);
		free(parsenv);
	}
}

void		ft_cd(t_conf *config, char **cmd_split)
{
	char	*path;

	if (!(path = ft_returnpath(config, *(cmd_split + 1))))
		return ;
	if (ft_access(path, DIRECTORY))
	{
		ft_modifypwd(config, "OLDPWD");
		chdir(path);
		ft_modifypwd(config, "PWD");
	}
	free(path);
}
