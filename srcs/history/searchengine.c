/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchengine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:07:27 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/14 12:07:55 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_searchinhistory(t_stream *stream)
{
	ft_decr_history(&(stream->shindex));
	while (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex]
		&& !(ft_strstr(stream->config->history[stream->shindex], stream->search)))
		ft_decr_history(&(stream->shindex));
}

void		ft_searchengine(t_stream *stream)
{
	if (!(stream->search))
	{
		stream->search = ft_strnew(1);
		if (stream->command && stream->command[0])
			stream->searchbuf = ft_strdup(stream->command);
		ft_sprompt(stream);
	}
	else
	{
		ft_prompt_reset(stream);
		free(stream->search);
		stream->search = NULL;
	}
}
