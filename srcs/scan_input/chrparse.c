/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:42 by tboos             #+#    #+#             */
/*   Updated: 2016/09/09 12:05:06 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_flushend(t_stream *stream)
{
	size_t		size;

	size = ft_strlen(stream->command + stream->pos);
	ft_putstr(stream->command + stream->pos);
	stream->pos += size;
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr ("   ");
		stream->pos += 3;
	}
	ft_erase(stream);
}

void			ft_flush(t_stream *stream)
{
	size_t		pos;

	pos = stream->pos;
	ft_flushend(stream);
	while (stream->pos != pos)
		ft_mvleft(stream);
}

static void		ft_append(t_stream *stream)
{
	size_t				pos;
	size_t				len;
	char				*kill;

	len = ft_strlen(stream->buf);
	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + len))
			&& (stream->state = -2))
			return ;
		ft_strncpy(stream->command, kill, pos);
		ft_strcpy(stream->command + pos, stream->buf);
		ft_strcpy(stream->command + pos + len, kill + pos);
	}
	else if (!(stream->command = ft_strdup(stream->buf)))
		stream->state = -2;
	ft_push_history(stream, stream->config);
	ft_flush(stream);
	while (len--)
		ft_mvright(stream);
}

static int		ft_chrmatch(t_stream *stream)
{
	static ssize_t		match[] = {CLF, SUP, CHT, DEL,
		LEF, RIG, UPP, DOW,
		CLEF, CRIG, CUPP, CDOW, END, HOM, NUL};
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
	static void			(*ftab[])(t_stream *) = {&ft_sup, &ft_autocomp,
			&ft_del, &ft_left, &ft_right, &ft_up, &ft_down,
			&ft_ctrlleft, &ft_ctrlright, &ft_ctrlup, &ft_ctrldown,
			&ft_goend, &ft_gohome};

	if (!(match = ft_chrmatch(stream)))
		return (0);
	if (match == -1)
		ft_append(stream);
	else if (match > 0)
		(*ftab[match - 1])(stream);
	return (1);
}
