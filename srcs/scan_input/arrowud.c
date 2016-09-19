/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:16 by tboos             #+#    #+#             */
/*   Updated: 2016/09/19 16:12:10 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goend(t_stream *stream)
{
	if (stream->command)
		while (stream->command[stream->pos])
			ft_right(stream);
}

void	ft_gohome(t_stream *stream)
{
	while (stream->pos)
		ft_left(stream);
}

void	ft_ctrlup(t_stream *stream)
{
	size_t		col;

	if (stream->search)
		ft_searchengine(stream);
	col = stream->col;
	while (col--)
		ft_left(stream);
}

void	ft_ctrldown(t_stream *stream)
{
	size_t		col;

	if (stream->search)
		ft_searchengine(stream);
	col = stream->col;
	while (col--)
		ft_right(stream);
}
