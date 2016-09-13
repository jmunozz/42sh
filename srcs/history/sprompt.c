/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprompt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 16:23:59 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/13 16:43:05 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sprompt(t_stream *stream)
{
	char	*buf;

	buf = (stream->search && stream->search[0]) ?
		ft_strjoin("back-i-search: ", stream->search) :
		ft_strdup("back-i-search:");
	ft_underline_mess(buf, stream);
	free(buf);
}
