/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checknewline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:59:34 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/21 16:38:36 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checknewline(t_stream *stream)
{
	size_t	pos;
	size_t	i;

	if (!stream->command || stream->command[stream->pos] != '\n'
		|| !stream->pos)
		return ;
	pos = stream->pos;
	i = 0;
	stream->tput = "le";
	while (--pos)
		if (stream->command[pos] == '\n' && (pos += 1))
			break ;
	if (pos)
		while (++i < (stream->col - (stream->pos - pos)))
			ft_tputs(stream);
	else
		while (++i < (stream->col - stream->pos - stream->config->prompt_len))
			ft_tputs(stream);
}
