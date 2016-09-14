/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprompt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 16:23:59 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/14 12:42:03 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_flushsearch(t_stream *stream)
{
	size_t		size;
	int			index;

	if (stream->command && stream->command[0])
	{
		size = ft_strlen(stream->search);
		index = ft_strstri(stream->command, stream->search);
		write(1, stream->command, index);
		ft_putstr("\033[4m");
		ft_putstr(stream->search);
		ft_putstr("\033[00m");
		ft_putstr(stream->command + index + size);
		stream->pos += index;
	}
}

void	ft_sprompt(t_stream *stream)
{
	char	*buf;

	buf = (stream->search && stream->search[0]) ?
		ft_strjoin("back-i-search: ", stream->search) :
		ft_strdup("back-i-search:");
	ft_underline_mess(buf, stream);
	free(buf);
}
