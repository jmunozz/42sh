#include "minishell.h"

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
	stream->pos++;
}

static int		ft_chrmatch(t_stream *stream)
{
	static int	match[] = {CLF, CBS, CHT, DEL, NUL};
	int			i;

	i = 0;
	while (match[i] != 0)
	{
		if ((int)stream->buf[0] == match[i])
			return (i);
		i++;
	}
	if (ft_isprint(stream->buf[0])
		return (-1);
	return (-2);
}

int				ft_chrparse(t_stream *stream)
{
	int			match;
	static void tab[3](t_stream *) = {&ft_cbs, &ft_autocomp, &ft_del};

	if (!(match = ft_chrmatch(stream)))
		return (0);
	if (match == -1)
	{
		ft_putstr(stream->buf);
		ft_append(stream);
	}
	else if (match > 0 && match <= 5)
		(*ftab[match - 1])(config);
	return (1);
}
