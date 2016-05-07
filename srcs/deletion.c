#include "minishell.h"

int		ft_putcharint(int	i)
{
	char		c;

	c = i;
	ft_putchar(c);
	return(c);
}

void	ft_clean_field(t_stream *stream)
{
	ft_goend(stream);
	while (stream->pos)
	{
		ft_left(stream);
		ft_erase(stream);
	}
}

void	ft_erase(t_stream *stream)
{
	stream->tput = tgetstr("dc", NULL);
	ft_tputs(stream);
}

void	ft_del(t_stream *stream)
{
	size_t	pos;

	if (stream->command && stream->pos)
	{
		ft_mvleft(stream);
		pos = stream->pos - 1;
		while (stream->command[++pos])
			stream->command[pos] = stream->command[pos + 1];
		ft_flush(stream);
	}
}

void	ft_sup(t_stream *stream)
{
	size_t	i;
	size_t	pos;

	if (stream->command && stream->command[stream->pos])
	{
		i = -1;
		pos = stream->pos;
		while (stream->command[pos + ++i])
			stream->command[pos + i] = stream->command[pos + i + 1];
		ft_flush(stream);
	}
}
