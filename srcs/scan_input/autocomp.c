/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2016/11/07 11:50:10 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_marge(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' || c == ';'|| c == ' ')
		return (1);
	return (0);
}

static char *ft_get_path(t_stream *stream, t_globing *data)
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
	data->end = i;
	path = ft_strnew(len);
	path = ft_strncpy(path, &(stream)->command[j], len);
	stream->pos = j;
	if ((ft_strstri(path, "*")) != -1)
		return (path);
	return (NULL);
}

void	ft_autocomp(t_stream *stream)
{
	t_globing	glob;
	int			end;

	ft_bzero(stream->buf, 4);
	ft_bzero(&glob, sizeof(void*));
	if ((glob.path = ft_get_path(stream, &glob)))
		ft_loop_path(stream, &glob);
	else
		ft_underline_mess("NO", stream);
	ft_strdel(&glob.path);
}
