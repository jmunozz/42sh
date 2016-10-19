/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/09/28 13:24:08 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_list(t_list *elem)
{
	if (!elem->data_size)
	{
		ft_putstr("\nargv :\n");
		ft_putstrtab((char **)(elem->data), '\n');
		ft_putchar('\n');
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

	if ((begin = ft_lexer(cmd)))
		ft_lstiter(begin, ft_print_list);
	ft_freegiveone((void**)&cmd);
	ft_parse(begin, config);
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
