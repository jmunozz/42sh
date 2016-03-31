/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 13:23:57 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_command(t_config *config, char *cmd)
{
	t_arguments	av;

	ft_push_history(cmd, config);
	if ((av.argv = ft_strsplit(cmd, ' ')))
		while (av.argv)
		{
			av.memo = ft_strtabdiv(av.argv, ";");
			if (ft_builtin(av.argv, config))
				;
			else if ((cmd = ft_return_binpath(config, av.argv[0])))
				ft_access_exec(cmd, av.argv, config);
			else if (av.argv[0][0] == '.' || av.argv[0][0] == '/')
				ft_access_exec(av.argv[0], av.argv, config);
			else
				FT_PUTSTRFD("minishell: command not found: ",
						av.argv[0], "\n", 2);
			ft_strtabfree(av.argv);
			av.argv = av.memo;
		}
}

void		ft_minishell(t_config *config)
{
	char		*cmd;

	while (ft_prompt(config) && (cmd = ft_streamscan(config, 0)))
		ft_run_command(config, cmd);
}
