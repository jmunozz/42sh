/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 09:11:54 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:25:00 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static void	ft_setsignals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		ft_error(NULL, SIG_INT, KEEP);
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		ft_error(NULL, SIG_STOP, KEEP);
}

int			main(int argc, char **argv, char **env)
{
	t_conf	*config;

	config = NULL;
	if (argc != 1 || !argv)
		return (0);
	ft_setsignals();
	if (env)
		config = ft_fillconf(env);
	if (config)
	{
		if (!(config->term))
			ft_error(NULL, TERM_NOTFOUND, KEEP);
		ft_hashtable(config);
		ft_minishell(config);
	}
	return (0);
}
