#include "minishell.h"

void	ft_del(t_stream *stream)
{
	size_t	i;
	size_t	pos;

	if (stream->command && stream->pos)
	{
		ft_mvleft(stream);
		i = -1;
		pos = stream->pos;
		while (stream->command[pos + ++i])
			stream->command[pos + i] = stream->command[pos + i + 1];
		ft_putstr(stream->command + pos);
		stream->pos += ft_strlen(stream->command + pos);
		ft_erase(stream);
		while (--i)
			ft_mvleft(stream);
	}
}

void	ft_sup(t_stream *stream)
{
	char	*c;
	size_t	i;

dprintf(1, "sup");
	c = stream->command;
	if (c && c[stream->pos])
	{
		c = c + stream->pos;
		i = strlen(c);
		while (*(++c))
		{
			*c = *(c + 1);
		}
		ft_putstr(stream->command + stream->pos);
		stream->pos += i - 1;
		ft_erase(stream);
		while (--i)
			ft_mvleft(stream);
	}
}
