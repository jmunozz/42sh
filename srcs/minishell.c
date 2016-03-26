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

/*
**Extern while allways true !
*/
void		ft_minishell(t_config *config)
{
	char		*command;
	t_arguments	av;

	while (ft_prompt(config) && (command = ft_streamscan(config)))
	{
		ft_push_history(command, config);
		av.argv = ft_strsplit(command, ' ');
		while (av.argv)
		{
			av.memo = ft_strtabdiv(av.argv, ";");
			if (ft_builtin(av.argv, config));
			else if ((command = ft_return_binpath(config, av.argv[0])))
				ft_access_exec(command, av.argv, config);
			else
				ft_access_exec(av.argv[0], av.argv, config);
			ft_strtabfree(av.argv);
			av.argv = av.memo;
			command = NULL;
		}
	}
}
