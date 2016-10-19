/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 09:50:49 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:15:34 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_exit(t_conf *config, char **cmd_split)
{
	int	exit_value;

	exit_value = 0;
	ft_free_split(config->env);
	free(config->env);
	ft_free_bin(&(config->bin));
	free(config);
	if (*(cmd_split + 1))
		exit_value = ft_atoi(*(cmd_split + 1));
	exit(exit_value);
}
