/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchengine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:07:27 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/13 12:32:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		ft_searchengine(t_stream *stream)
{
	if (!(stream->search))
	{
		stream->search = ft_strnew(1);
		ft_putstr("\nback-i-search: ");
	}
	else
	{
		free(stream->search);
		stream->search = NULL;
	}
}
