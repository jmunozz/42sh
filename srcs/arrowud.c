#include "minishell.h"

void	ft_up(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}

void	ft_down(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}

void	ft_ctrlup(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}

void	ft_ctrldown(t_stream *stream)
{
	ft_bzero(stream->buf, 4);
}
