/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/09/12 15:26:13 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_term(t_config *config)
{
	if (tcgetattr(STDIN_FILENO, &(config->termios_backup)) == -1
		|| !ft_memcpy(&(config->termios), &(config->termios_backup),
		sizeof(t_termios)))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd("fail to set terminal, problems may occur\n", 2);
		return false;
	}
	config->termios.c_lflag &= ~(ICANON | ECHO);
	config->termios.c_cc[VMIN] = 1;
	config->termios.c_cc[VTIME] = 0;
	return true;
}

static void		ft_termios_handle(t_config *config, int mode)
{
	static char		state = 0;

	if (!state && ft_init_term(config))
		state = 1;
	if (mode && state)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &(config->termios)) == -1)
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd("fail to set terminal, problems may occur\n", 2);
			return ;
		}
	}
	else if (!mode && state)
		tcsetattr(STDIN_FILENO, TCSANOW, &(config->termios_backup));
	return ;
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
	if (stream->config->term_state)
		ft_underline_mess(" ", stream);
}

char		*ft_streamscan(t_config *config, t_stream *stream, int fd)
{
	ft_bzero(stream, sizeof(t_stream));
	ft_freegiveone((void **)(&(config->history[config->hindex])));
	stream->fd = fd;
	stream->config = config;
	ft_termios_handle(config, 1);
	ft_winsize();
	ft_scan(stream);
	ft_termios_handle(config, 0);
	if (stream->state < 0)
	{
		ft_putstr_fd("\nminishell: error while scanning command\n", 2);
		return (NULL);
	}
	if (stream->command && stream->command[0]
		&& stream->shindex == config->hindex)
	{
		ft_push_history(stream, config);
		ft_incr_history(&(config->hindex));
	}
	ft_putchar('\n');
	return (stream->command);
}
