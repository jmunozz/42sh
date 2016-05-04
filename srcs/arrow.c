#include "minishell.h"

void	ft_left(t_stream *stream)
{
	if (stream->pos)
		ft_mvleft(stream);
}

void	ft_right(t_stream *stream)
{
	if (stream->command && ft_strlen(stream->command) != stream->pos)
		ft_mvright(stream);
}

void	ft_up(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}

void	ft_down(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}
