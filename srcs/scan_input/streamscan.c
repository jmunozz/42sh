/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/09/09 08:34:00 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_termios_handle(t_config *config, int mode)
{
	t_termios		minishell;
	static char		state = 'n';

	if (mode && state == 'n')
	{
		if (tcgetattr(STDIN_FILENO, &(config->termios_backup)) == -1
			|| !ft_memcpy(&minishell, &(config->termios_backup),
			sizeof(t_termios)))
			return (1);
		minishell.c_lflag &= ~(ICANON | ECHO);
		minishell.c_cc[VMIN] = 1;
		minishell.c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &minishell) == -1)
			return (1);
		state = 'y';
	}
	else if (state == 'y')
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(config->termios_backup));
		state = 'n';
	}
	return (1);
}

static int	ft_try_again(t_stream *stream)
{
	if ((stream->ret = read(stream->fd, stream->buf, 8)) < 0)
		return false;
	return true;
}

static void	ft_scan(t_stream *stream)
{
	stream->shindex = stream->config->hindex;
	while (1)
	{
		ft_bzero(stream->buf, 9);
		if (((stream->ret = read(stream->fd, stream->buf, 8)) < 0
			&& !ft_try_again(stream) && (stream->state = -1))
			|| (!ft_chrparse(stream) && (!stream->command
			|| ft_quotecheck(stream)))
			|| stream->state < 0)
			break ;
	}
	ft_underline_mess(" ", stream);
}

char		*ft_streamscan(t_config *config, t_stream *stream, int fd)
{
	ft_bzero(stream, sizeof(t_stream));
	stream->fd = fd;
	stream->config = config;
	ft_termios_handle(config, 1);
	if (!config->term_state && (!(stream->term = getenv("TERM"))
		|| !tgetent(NULL, stream->term)))
		ft_term_error(config);
	ft_winsize();
	ft_scan(stream);
	ft_termios_handle(config, 0);
	if (stream->state < 0)
	{
		if (config->history[config->hindex])
			ft_freegiveone((void **)(&(config->history[config->hindex])));
		ft_putstr_fd("\nminishell: error while scanning command\n", 2);
		return (NULL);
	}
	if (stream->command && config->history[config->hindex])
	{
		ft_incr_history(&(config->hindex));
		ft_freegiveone((void **)&(config->history[config->hindex]));
	}
	ft_putchar('\n');
	return (stream->command);
}
