#include "minishell.h"

int				ft_autocomp(t_stream *stream)
{
	if (stream->buf[0] != '\t')
		return (0);
	ft_bzero(stream->buf, 4);
	return (1);
}

static void		ft_append(t_stream *stream)
{
	if ((stream->kill = stream->command))
	{
		if (!(stream->command = ft_strjoin(stream->command, stream->buf)))
			stream->state = -2;
		free(stream->kill);
	}
	else if (!(stream->command = ft_strdup(stream->buf)))
		stream->state = -2;
}

int				ft_chrparse(t_stream *stream)
{
	if (ft_autocomp(stream))
		return (1);
	if (stream->buf[0] == '\n')
		return (0);
	ft_putstr(stream->buf);
	ft_append(stream);
	return (1);
}
