/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:16 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 11:02:43 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_up(t_stream *stream)
{
	ft_decr_history(&(stream->shindex));
	if (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex])
	{
		ft_clean_field(stream);
		stream->command = ft_strdup(stream->config->history[stream->shindex]);
		ft_flushend(stream);
	}
	else
		ft_incr_history(&(stream->shindex));
}

void	ft_down(t_stream *stream)
{
	if (stream->shindex != stream->config->hindex)
	{
		ft_incr_history(&(stream->shindex));
		ft_clean_field(stream);
		stream->command = ft_strdup(stream->config->history[stream->shindex]);
		ft_flushend(stream);
	}
}

void	ft_decr_history(int *hindex)
{
	if (*hindex > 0)
		(*hindex)--;
	else
		*hindex = HISTORY_SIZE;
}

void	ft_incr_history(int *hindex)
{
	if (*hindex < HISTORY_SIZE - 1)
		(*hindex)++;
	else
		*hindex = 0;
}

void	ft_push_history(t_stream *stream, t_config *config)
{
	stream->shindex = config->hindex;
	if (stream->command && stream->command[0])
	{
		if (config->history[config->hindex])
			ft_freegiveone((void **)&(config->history[config->hindex]));
		config->history[config->hindex] = stream->command;
	}
}
