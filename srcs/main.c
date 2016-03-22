/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/03/18 18:37:31 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_initerror(void)
{
		ft_putstr_fd("minishell: init error", 2);
		return (1);
}

int		main(int ac, char **av, char **env)
{
	t_config	*config;

	if (ac)
		(void)av;
	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
		return (ft_initerror());
	config->env = NULL;
	config->exe = NULL;
	if (!(config->env = ft_strtabdup(env))
		|| !(ft_pathtohash(config))
		|| !(ft_prompt(config)))
	{
		ft_free_config(config);
		return (ft_initerror());
	}
	ft_minishell(config);
	return (ft_status(0));
}
