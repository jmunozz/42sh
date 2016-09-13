/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:20:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/13 12:32:55 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_sappend(t_stream *stream)
{
	size_t				len;
	char				*kill;

	len = ft_strlen(stream->buf);
	if ((kill = stream->search))
	{
		stream->search = ft_strjoin(stream->search, stream->buf);
		free(kill);
	}
}
