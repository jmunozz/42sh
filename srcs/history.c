/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:16 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:21:23 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_push_history(char *command, t_config *config)
{
	static short	i = 0;

	if (command && *command)
	{
		if (config->history[i])
			free(config->history[i]);
		config->history[i] = command;
	}
	if (i < 254)
		i++;
	else
		i = 0;
}
