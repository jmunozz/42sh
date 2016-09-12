/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 20:59:10 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/12 10:14:37 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_down_search(t_stream *stream)
{
	char	*com;
	size_t	len;

	com = stream->config->history[stream->config->hindex];
	len = ft_strlen(com);
	while (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex]
		&& ft_strncmp(com, stream->config->history[stream->shindex], len))
		ft_incr_history(&(stream->shindex));
}

void	ft_down(t_stream *stream)
{
	if (stream->shindex != stream->config->hindex)
	{
		ft_incr_history(&(stream->shindex));
		if (stream->config->history[stream->config->hindex]
			&& stream->config->history[stream->config->hindex][0])
			ft_down_search(stream);
		if (stream->config->history[stream->shindex]
			&& ft_freegiveone((void **)&(stream->command))
			&& !(stream->command = ft_strdup(stream->config->history[stream->shindex])))
		{
			stream->state = -2;
			return ;
		}
		else if (stream->config->hindex == stream->shindex)
			ft_freegiveone((void **)&(stream->command));
		if (stream->command)
			ft_winsize();
		else
		{
			ft_prompt_reset(stream);
			stream->pos = 0;
		}
	}
}
