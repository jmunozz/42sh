/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/09/15 11:06:29 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_run_command(t_config *config, char *cmd)
{
	t_arguments	av;

	if ((av.argv = ft_strsplit(cmd, ' ')) && ft_freegiveone((void **)&cmd))
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
				ft_error(SHNAME, "command not found", av.argv[0], CR_ERROR);
			ft_strtabfree(av.argv);
			av.argv = av.memo;
		}
}

void		ft_minishell(t_config *config)
{
	char		*cmd;
	t_stream	stream;

	if (ft_signal())
		ft_shell_exit(config, NULL);
	ft_load_history(config);
	ft_save_stream(&stream);
	while (1)
		if ((cmd = ft_streamscan(config, &stream, 0)))
			ft_run_command(config, cmd);
}
