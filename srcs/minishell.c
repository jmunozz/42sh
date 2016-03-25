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

void		ft_minishell(t_config *config)
{
	char	*command;
	char	**argv;

	while (ft_prompt(config) && (command = ft_streamscan(config)))
	{
		argv = NULL;
		ft_push_history(command, config);
		if (!(argv = ft_strsplit(command, ' ')));
		else if (!ft_strcmp(argv[1], "exit"))
			break ;
		else if (ft_builtin(argv, config))
			ft_putchar('\n');
		else if ((command = ft_return_binpath(config, argv[0])))
			ft_fewef(command, argv, config->env);
		else
			ft_access_exec(argv, config->env);
		if (argv)
			ft_strtabfree(argv);
	}
	exit(ft_status(0));
}
