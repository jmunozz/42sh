/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 14:17:37 by tboos            ###   ########.fr       */
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
	else if (elem->data_size == OP)
		FT_PUTSTRFD("\nop :\n", (char*)elem->data, "\n", 1);
	else if (elem->data_size == JOB)
		ft_print_jobs(elem->data, NULL);
	else if (elem->data_size == PIPE)
	{
		ft_putstr("\npipe :\n");
		ft_putnbr(((int*)elem->data)[0]);
		ft_putnbr(((int*)elem->data)[1]);
		ft_putchar('\n');
	}
}

void		ft_run_command(t_config *config)
{
	config->shell_state = RUNNING_COMMAND;
	if ((config->chimera = ft_lexer(config->command)))
	{
		if (!ft_quote(config->chimera, config)
			|| !ft_herringbone(config->chimera, config))
			ft_freelist(&config->chimera);
		else
		{
			ft_lstiter(config->chimera, ft_print_list);
			ft_parse(config);
		}
	}
	ft_freegiveone((void**)&config->command);
}

void		ft_minishell(t_config *config)
{
	t_stream	stream;

	if (ft_signal())
		ft_shell_exit(config);
	ft_load_history(config);
	ft_save_stream(&stream);
	config->shell_state = SCANNING_COMMAND;
	while (1)
		if ((config->command = ft_streamscan(config, &stream, STDIN_FILENO)))
		{
			ft_run_command(config);
			if (config->shell_state != RUNNING_COMMAND)
				ft_gotonextline(&stream);
			config->shell_state = SCANNING_COMMAND;
		}
}
