/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:44:56 by tboos             #+#    #+#             */
/*   Updated: 2016/11/17 18:36:38 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stream		*ft_save_stream(t_stream *stream)
{
	static t_stream	*saved = NULL;

	if (stream)
		saved = stream;
	return (saved);
}

void			ft_secure_prompt(t_stream *stream)
{
	ft_prompt(stream->config);
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr(" ");
		stream->tput = "le";
		ft_tputs(stream);
	}
}

/*
**Fill stream->row and stream->col with winsize structure w wich contents screen
**width and height (in characters).
*/

void			ft_prompt_reset(t_stream *stream)
{
	struct winsize	w;
	size_t			col;
	size_t			lin;

	ioctl(stream->fd, TIOCGWINSZ, &w);
	col = w.ws_col;
	stream->row = w.ws_row;
	if (stream->col)
	{
		ft_gohome(stream);
		lin = stream->config->prompt_len / stream->col;
		stream->tput = "up";
		while (lin--)
			ft_tputs(stream);
		stream->tput = "le";
		while ((stream->col)--)
			ft_tputs(stream);
		stream->tput = "cd";
		ft_tputs(stream);
	}
	stream->col = col;
	ft_secure_prompt(stream);
}

void			ft_flush_command(t_stream *stream)
{
	unsigned int	pos;

	pos = stream->pos;
	if (stream->command)
	{
		stream->pos = 0;
		ft_flushend(stream);
		ft_gomatch(stream, pos);
	}
}

void			ft_winsize(void)
{
	t_stream		*stream;

	stream = ft_save_stream(NULL);
	ft_prompt_reset(stream);
	ft_flush_command(stream);
	if (COMP_STATE)
		ft_comp_print(stream);
	ft_sigwinch(1);
}
