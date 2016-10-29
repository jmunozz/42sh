/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2016/10/28 15:59:19 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_marge(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' || c == ';'|| c == ' ')
		return (1);
	return (0);
}

static char *ft_get_path(t_stream *stream)
{
	int		i;
	int		j;
	int		len;
	char	*path;

	i = stream->pos;
	len = 0;
	while (i >= 0 && (!ft_check_marge(stream->command[i])))
		i--;
	j = ++i;
	while (stream->command[i] && (!ft_check_marge(stream->command[i])) && ++len)
		i++;
	path = ft_strnew(len);
	path = ft_strncpy(path, &(stream)->command[j], len);
	if ((ft_strstri(path, "*")) != -1)
		return (path);
	return (NULL);
}

void	ft_autocomp(t_stream *stream)
{
	t_globing	data;

	ft_bzero(stream->buf, 4);
	if ((data.path = ft_get_path(stream)))
		ft_loop_path(stream, &data);
	else
		ft_underline_mess("NO", stream);
	ft_strdel(&data.path);
}
