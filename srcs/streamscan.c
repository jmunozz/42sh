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

int			ft_termios_handle(int mode)
{
	struct termios	minishell;
	static char		state = 'n';

	if (mode && state == 'n')
	{
		if (tcgetattr(STDIN_FILENO, &termios_backup) == -1
			|| !ft_memcpy(&minishell, &termios_backup, sizeof(struct termios)))
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
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
		state = 'n';
	}
	return (1);
}

static void	ft_arrow(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}

static void	ft_scan(t_stream *stream)
{
	while (1)
	{
		if ((stream->ret = read(stream->fd, stream->buf, 4)) < 0 && (stream->state = -1))
			break ;
//dprintf(1, "%s\n", stream->buf);
		if (stream->ret == 4)
			ft_arrow(stream);
		else if (!ft_chrparse(stream) || stream->state < 0)
			break ;
		ft_bzero(stream->buf, 4);
	}
}

char		*ft_streamscan(t_config *config, int fd)
{
	t_stream		stream;

	ft_bzero(&stream, sizeof(t_stream));
	stream.fd = fd;
	stream.config = config;
	if (config)
		ft_termios_handle(1);
	ft_scan(&stream);
	if (stream.state < 0)
	{
		ft_putstr_fd("minishell: error while scanning command\n", 2);
		return (NULL);
	}
	ft_putchar('\n');
	return (stream.command);
}
