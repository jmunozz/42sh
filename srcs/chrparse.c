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
	static ssize_t	match[] = {CLF, SUP, CHT, DEL, LEF, RIG, UPP, DOW,
		CLEF, CRIG, CUPP, CDOW, NUL};
	int					i;

	i = 0;
//printf("\nbuf   = %lx\n", ((ssize_t *)(stream->buf))[0]);
	while (match[i])
	{
//printf("\nmatch = %lx\n", match[i]);
		if (((ssize_t *)(stream->buf))[0] == match[i])
			return (i);
		i++;
	}
	if (ft_isprint(stream->buf[0]))
		return (-1);
	return (-2);
}

int				ft_chrparse(t_stream *stream)
{
	int					match;
	static void (*ftab[])(t_stream *) = {&ft_sup, &ft_autocomp, &ft_del,
		&ft_left, &ft_right, &ft_up, &ft_down, &ft_ctrlleft, &ft_ctrlright,
		&ft_ctrlup, &ft_ctrldown};

	if (!(match = ft_chrmatch(stream)))
		return (0);
	if (match == -1)
	{
		ft_putstr(stream->buf);
		ft_append(stream);
	}
	else if (match > 0)
		(*ftab[match - 1])(stream);
	return (1);
}
