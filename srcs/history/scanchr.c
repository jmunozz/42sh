/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:20:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/16 15:01:45 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_modifycommand(t_stream *stream)
{
	if (stream->config->history[stream->shindex]
		&& stream->config->history[stream->shindex][0])
	{
		ft_freegiveone((void **)&(stream->command));
		stream->command = ft_strdup(stream->config->history[stream->shindex]);
	}
}

void		ft_sappend(t_stream *stream)
{
	char				*kill;

	if ((kill = stream->search))
	{
		stream->search = ft_strjoin(stream->search, stream->buf);
		free(kill);
		stream->shindex = stream->config->hindex;
		ft_searchinhistory(stream);
		ft_modifycommand(stream);
		ft_winsize();
		ft_sprompt(stream);
	}
}

void	ft_sdel(t_stream *stream)
{
	if (stream->search[0])
	{
		stream->search[ft_strlen(stream->search) - 1] = '\0';
		stream->shindex = stream->config->hindex;
		if (stream->search[0])
			ft_searchinhistory(stream);
		ft_modifycommand(stream);
		ft_winsize();
		ft_sprompt(stream);
	}
}
