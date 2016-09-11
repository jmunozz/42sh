/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 20:15:54 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/11 20:58:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_up_search(t_stream *stream)
{
	while (stream->shindex != stream->config->hindex
	&& stream->config->history[stream->shindex]
	&& (ft_strncmp(stream->command_buf,
			stream->config->history[stream->shindex],
			ft_strlen(stream->command_buf))))
			ft_decr_history(&(stream->shindex));
}

void	ft_up(t_stream *stream)
{
	 ft_decr_history(&(stream->shindex));
	 if (stream->command_buf)
	 	ft_up_search(stream);
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
