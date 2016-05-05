#include "minishell.h"

void			ft_flush(t_stream *stream)
{
	size_t		size;
	size_t		pos;

	pos = stream->pos;
	size = ft_strlen(stream->command + pos);
	ft_putstr(stream->command + pos);
	stream->pos += size;
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putchar(' ');
		stream->pos++;
	}
	ft_erase(stream);
	while (stream->pos != pos)
		ft_mvleft(stream);
}

static void		ft_append(t_stream *stream)
{
	size_t				pos;
	char				*kill;

	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + 1))
			&& (stream->state = -2))
			return ;
		ft_strncpy(stream->command, kill, pos);
		stream->command[pos] = stream->buf[0];
		ft_strcpy(stream->command + pos + 1, kill + pos);
		free(kill);
	}
	else if (!(stream->command = ft_strdup(stream->buf)))
		stream->state = -2;
	ft_flush(stream);
	ft_mvright(stream);
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
		ft_append(stream);
	else if (match > 0)
		(*ftab[match - 1])(stream);
	return (1);
}
