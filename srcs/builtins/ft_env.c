/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 14:19:42 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:23:36 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static char	**ft_parseparam(char **cmd_split, unsigned char *params)
{
	int		i;

	while (cmd_split && *cmd_split && ft_strcmp(*cmd_split, "--")
			&& *cmd_split[0] == '-')
	{
		i = 0;
		while ((*cmd_split)[++i] != '\0')
			if ((*cmd_split)[i] == 'i')
				*params |= PARAM_I;
		cmd_split++;
	}
	return (cmd_split);
}

static void	ft_createenv(t_conf *config, char *cmd_split)
{
	char	*split_final[4];
	char	**split;

	if (!(split = ft_strsplit(cmd_split, '=')))
		return ;
	if (!(config->env))
	{
		if (!(config->env = ft_memalloc(sizeof(char*) * 2)))
			return ;
		(config->env)[0] = NULL;
		(config->env)[1] = NULL;
	}
	split_final[0] = "env";
	split_final[1] = split[0];
	split_final[2] = split[1];
	split_final[3] = NULL;
	ft_setenv(config, (char**)split_final);
	ft_free_split(split);
	free(split);
}

void		ft_env(t_conf *config, char **cmd_split)
{
	unsigned char	params;
	t_conf			env_send;

	if (!*(cmd_split + 1))
	{
		ft_printenv(config->env);
		return ;
	}
	params = 0;
	cmd_split = ft_parseparam(cmd_split + 1, &params);
	env_send.env = (params & PARAM_I) ? NULL :
		ft_fillenv(config->env, ft_splitsize(config->env));
	while (cmd_split && *cmd_split && ft_strchr(*cmd_split, '='))
	{
		ft_createenv(&env_send, *cmd_split);
		cmd_split++;
	}
	if (cmd_split && *cmd_split)
		ft_execcmd(ft_findcmd(*cmd_split, ft_hashsearch(config, *cmd_split)),
				cmd_split, &env_send);
	if (env_send.env)
	{
		ft_free_split(env_send.env);
		free(env_send.env);
	}
}
