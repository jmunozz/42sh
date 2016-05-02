#include "minishell.h"

int				ft_autocomp(t_stream *stream)
{
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

static int		ft_chrmatch(t_stream *stream)
{
	static int	match[] = {CLF, CBS, CHT, SPA, DQU, SQU, POP, PCL, COP, CCL,
							AOP, ACL, DEL, NUL};
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

	if (!(match = stream->buf[0]))
		return (0);
	ft_putstr(stream->buf);
	ft_append(stream);
	return (1);
}
