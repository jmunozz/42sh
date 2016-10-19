/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2016/10/17 16:46:05 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/autocomp.h"

/*
   static void	get_autocomp(t_stream *stream)
   {
   }

   static char	*ft_last_separators(const char *str, char c)
   {
   int i;
   char *ret;

   i = 0;
   if (!str || !*str)
   return (NULL);
   while (str[i])
   i++;
   if (str[--i] == c)
   return (NULL);
   if ((ret = ft_strrchr(str, c)))
   return (ret + 1);
   return (NULL);
   }
   */

char	*list_to_char(t_list *list)
{
	char *str;

	str = ft_strnew(1000);
	while (list)
	{
		str = ft_strcat(str, (char*)list->data);
		str = ft_strcat(str, "\n");
		list = list->next;
	}
	return (str);
}

int		ft_is_separator(char c)
{
	if (c == ';')
		return (1);
	if (c == '"')
		return (1);
	if (c == '&')
		return (1);
	if (c == '|')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int		get_mode(int len, char *str, t_stream *stream)
{
	int		i;
	char	co;

	co = 0;
	i = (stream->pos) - len - 1;
	while (i >= 0 && str[i] != '|' && str[i] != ';')
	{
		if (str[i] != ' ' && str[i] != '|' && str[i] != ';')
			co = 1;
		i--;
	}
	if (!len)
		return (!co ? 1 : 0);
	return (!co ? 3 : 2);
}


char	*get_begin(int i, char *str, int *len)
{
	while (i >= 0 && !ft_is_separator(str[i]))
	{
		i -= 1;
		*len += 1;
	}
	return (&(str[++i]));
}

void	ft_autocomp(t_stream *stream)
{
	int			buf_pos;
	int			len;
	int			mode;
	char		*begin;
	t_list		*list;

	list = NULL;
	len = 0;
	buf_pos = stream->pos;
	if (stream->command)
	{
		while (!ft_is_separator(stream->command[stream->pos])
				&& stream->command[stream->pos])
			ft_mvright(stream);
		begin = ft_strsub(get_begin(stream->pos - 1,
				stream->command,  &len), 0, len);
		mode = get_mode(len, stream->command, stream);
		//ft_underline_mess(begin, stream);
		build_list(&list, begin, mode, stream);
		if (list)
			ft_underline_mess(list_to_char(list), stream);
		else
			ft_underline_mess("pas de liste\n", stream);
		free(begin);
	}
}

