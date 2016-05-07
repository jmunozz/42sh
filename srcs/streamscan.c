/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/04/29 12:17:32 by tboos            ###   ########.fr       */
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

static void	ft_scan(t_stream *stream)
{
	stream->shindex = stream->config->hindex;
	while (1)
	{
		if (((stream->ret = read(stream->fd, stream->buf, 8)) < 0
			&& (stream->state = -1))
			|| !ft_chrparse(stream)
			|| stream->state < 0)
			break ;
		ft_bzero(stream->buf, 9);
	}
}

static void	ft_winrec(t_stream *stream)
{
	struct winsize	w;

	ioctl(stream->fd, TIOCGWINSZ, &w);
	stream->col = w.ws_col;
}

char		*ft_streamscan(t_config *config, int fd)
{
	t_stream		stream;

	ft_bzero(&stream, sizeof(t_stream));
	stream.fd = fd;
	stream.config = config;
	ft_termios_handle(config, 1);
	if (!config->term_state && (!(stream.term = getenv("TERM"))
		|| !tgetent(NULL, stream.term)))
		ft_term_error(config);
	ft_winrec(&stream);
	ft_scan(&stream);
	ft_termios_handle(config, 0);
	if (stream.state < 0)
	{
		if (config->history[config->hindex])
			ft_freegiveone((void **)(&(config->history[config->hindex])));
		ft_putstr_fd("minishell: error while scanning command\n", 2);
		return (NULL);
	}
	if (stream.command)
		ft_incr_history(&(config->hindex));
	ft_putchar('\n');
	return (stream.command);
}
