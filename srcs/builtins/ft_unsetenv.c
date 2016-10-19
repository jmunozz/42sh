/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 12:28:50 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/20 11:40:18 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

void		ft_unsetenv(t_conf *config, char **cmd_split)
{
	size_t	env_size;
	int		i_found;

	if (!*(cmd_split + 1))
	{
		ft_error(*cmd_split, FEW_ARG, KEEP);
		return ;
	}
	env_size = ft_splitsize(config->env);
	i_found = -1;
	while (++cmd_split && *cmd_split)
		if ((i_found = ft_findenv(config->env, *cmd_split)) != -1)
		{
			free(config->env[i_found]);
			config->env[i_found] = NULL;
			while (i_found + 1 < (int)env_size)
			{
				config->env[i_found] = config->env[i_found + 1];
				config->env[i_found + 1] = NULL;
				i_found++;
			}
		}
}
