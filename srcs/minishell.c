/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 21:22:41 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	ft_shell_exit(t_config *config)
{
	ft_free_config(config);
	exit(ft_status(0));
}

/*
**Extern while always true !
*/
void		ft_minishell(t_config *config)
{
	char	*command;
	char	**argv;

	while (ft_prompt(config) && (command = ft_streamscan(config)))
	{
		argv = NULL;
		ft_push_history(command, config);
		while ((argv = ft_strsplit(command, ' ')))
		{
			if (!ft_strcmp(argv[0], "exit"))
				ft_shell_exit(config);
			else if (ft_builtin(argv, config));
			else if ((command = ft_return_binpath(config, argv[0])))
				ft_fewef(command, argv, config->env);
			else
				ft_access_exec(argv, config->env);
			ft_strtabfree(argv);
			argv = NULL;
		}
	}
}
