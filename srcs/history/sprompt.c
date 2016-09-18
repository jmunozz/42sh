/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprompt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 16:23:59 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/16 14:58:45 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_flushsearch(t_stream *stream)
{
	size_t		size;
	int			index;

	if (stream->config->history[stream->shindex]
		&& (index = ft_strstri(stream->command, stream->search))  -1)
	{
		size = ft_strlen(stream->search);
		write(1, stream->command, index);
		ft_putstr("\033[4m");
		ft_putstr(stream->search);
		ft_putstr("\033[00m");
		ft_putstr(stream->command + index + size);
		stream->pos = ft_strlen(stream->command);
	}
}

void	ft_sprompt(t_stream *stream)
{
	char	*buf;
	int		index;

	buf = (stream->search && stream->search[0]) ?
		ft_strjoin("back-i-search: ", stream->search) :
		ft_strdup("back-i-search:");
	ft_underline_mess(buf, stream);
	if (stream->command && stream->search && stream->search[0]
			&& (index = ft_strstri(stream->command, stream->search)) != -1)
		ft_gomatch(stream, (size_t)index, &ft_mvleft);
	free(buf);
}
