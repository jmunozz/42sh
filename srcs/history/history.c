/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:16 by tboos             #+#    #+#             */
/*   Updated: 2016/09/09 08:12:53 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_up(t_stream *stream)
{
	ft_decr_history(&(stream->shindex));
	if (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex])
	{
		if (stream->config->history[stream->shindex] && !(stream->command
			= ft_strdup(stream->config->history[stream->shindex])))
		{
			stream->state = -2;
			return ;
		}
		if (stream->command)
			ft_winsize();
		else
			ft_prompt_reset(stream);
	}
	else
		ft_incr_history(&(stream->shindex));
}

void	ft_down(t_stream *stream)
{
	if (stream->shindex != stream->config->hindex)
	{
		ft_incr_history(&(stream->shindex));
		if (stream->config->history[stream->shindex] && !(stream->command
			= ft_strdup(stream->config->history[stream->shindex])))
		{
			stream->state = -2;
			return ;
		}
		else
			stream->command = NULL;
		if (stream->command)
			ft_winsize();
		else
		{
			ft_prompt_reset(stream);
			stream->pos = 0;
		}
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
		ft_freegiveone((void **)&(config->history[config->hindex]));
		config->history[config->hindex] = stream->command;
	}
}
