/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/11/04 17:26:52 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_gotonextline(t_stream *stream)
{
	ft_putchar('\n');
	stream->tput = "le";
	ft_tputs(stream);
	ft_tputs(stream);
}

void		ft_print_list(t_list *elem)
{
	if (!elem->data_size)
	{
		ft_putstr("\nargv :\n");
		if (elem->data)
			ft_putstrtab((char **)(elem->data), '\n');
		ft_putchar('\n');
	}
	else if (elem->data_size == SSHELL)
	{
		ft_putstr("\nSSHELL :\n");
		ft_lstiter((t_list *)elem->data, ft_print_list);
	}
	else
	{
		ft_putstr("\nop :\n");
		ft_putstr((char*)elem->data);
		ft_putchar('\n');
	}
}

void		ft_run_command(t_config *config, char *cmd)
{
	t_list		*begin;

	config->shell_state = RUNNING_COMMAND;
	if ((begin = ft_lexer(cmd)))
	{
		ft_herringbone(begin, config);
		ft_lstiter(begin, ft_print_list);
		ft_parse(begin, config);
	}
	ft_freegiveone((void**)&cmd);
}

void		ft_minishell(t_config *config)
{
	char		*cmd;
	t_stream	stream;

	if (ft_signal())
		ft_shell_exit(config, NULL);
	ft_load_history(config);
	ft_save_stream(&stream);
	config->shell_state = SCANNING_COMMAND;
	while (1)
		if ((cmd = ft_streamscan(config, &stream, 0)))
		{
			ft_run_command(config, cmd);
			if (config->shell_state != RUNNING_COMMAND)
				ft_gotonextline(&stream);
			config->shell_state = SCANNING_COMMAND;
		}
}
