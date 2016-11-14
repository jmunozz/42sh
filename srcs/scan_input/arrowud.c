/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:16 by tboos             #+#    #+#             */
/*   Updated: 2016/09/22 15:36:52 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goend(t_stream *stream)
{
	if (stream->command)
		while (stream->command[stream->pos])//tant qu'on est pas au bout de stream->command...
			ft_mvright(stream); //on bouge le curseur à droite.
}

void	ft_gohome(t_stream *stream)
{
	while (stream->pos) //tant qu'on est pas au début de la ligne de commande (stream->pos = 0)
		ft_mvleft(stream);//on bouge le curseur à gauche.
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
