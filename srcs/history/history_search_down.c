/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 20:59:10 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/11 21:03:53 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_down_search(t_stream *stream)
{
	while (stream->shindex != stream->config->hindex
	&& stream->config->history[stream->shindex]
	&& (ft_strncmp(stream->command_buf,
			stream->config->history[stream->shindex],
			ft_strlen(stream->command_buf))))
			ft_incr_history(&(stream->shindex));
}

void	ft_down(t_stream *stream)
{
	if (stream->shindex != stream->config->hindex)
	{
		ft_incr_history(&(stream->shindex));
		if (stream->command_buf)
			ft_down_search(stream);
		if (stream->config->history[stream->shindex] && !(stream->command
			= ft_strdup(stream->config->history[stream->shindex])))
		{
			stream->state = -2;
			return ;
		}
		else if (stream->shindex == stream->config->hindex)
			stream->command = stream->command_buf ? ft_strdup(stream->command_buf) : NULL;
		if (stream->command)
			ft_winsize();
		else
		{
			ft_prompt_reset(stream);
			stream->pos = 0;
		}
	}
}
