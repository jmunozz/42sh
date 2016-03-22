/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:02 by tboos             #+#    #+#             */
/*   Updated: 2016/03/18 18:11:52 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_config(t_config *config)
{
	if (config)
	{
		if (config->env)
			ft_strtabfree(config->env);
		if (config->exe)
			ft_strtabfree(config->exe);
		free(config);
	}
}
