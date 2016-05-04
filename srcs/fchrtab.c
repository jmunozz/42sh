#include "minishell.h"

void	ft_cbs(t_stream *stream)
{
	size_t	i;
	size_t	pos;

	if (stream->command && pos)
	{
		stream->pos--;
		stream->tput = tgetstr("le", NULL);
		tputs(stream->tput, stream->fd, &write);
		i = -1;
		pos = stream->pos;
		while (stream->command[pos + ++i])
			stream->command[pos + i] = stream->command[pos + i + 1];
		ft_putstr(stream->command + pos);
		ft_putchar(' ');
		while (--i)
			tputs(stream->tput, stream->fd, &write);
	}
}

void	ft_del(t_stream *stream)
{
	if (stream->pos)
		ft_bzero(stream->buf, 4);
}
