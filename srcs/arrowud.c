#include "minishell.h"

void	ft_goend(t_stream *stream)
{
	while (stream->command[stream->pos])
		ft_right(stream);
}

void	ft_gohome(t_stream *stream)
{
	while (stream->pos)
		ft_left(stream);
}

void	ft_ctrlup(t_stream *stream)
{
	size_t		col;

	col = stream->col;
	while (col--)
		ft_left(stream);
}

void	ft_ctrldown(t_stream *stream)
{
	size_t		col;

	col = stream->col;
	while (col--)
		ft_right(stream);
}
