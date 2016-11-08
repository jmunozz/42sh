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

#include "../includes/minishell.h"

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

char	*list_to_char(t_stream *stream, t_list *list)
{
	char *str;

	str = ft_strnew(1000);
	while (list)
	{
		str = ft_strcat(str, (char*)list->data);
		str = ft_strcat(str, "\n");
		list = list->next;
	}
	str = ft_strcat(str, "COMP_PAD = ");
	str = ft_strcat(str, ft_itoa((int)COMP_PAD));
	str = ft_strcat(str, "; COMP_COL =");
	str = ft_strcat(str, ft_itoa((int)COMP_COL));
	str = ft_strcat(str, "; COMP_SIZE_LIST = ");
	str = ft_strcat(str, ft_itoa((int)COMP_SIZE_LIST));
	str = ft_strcat(str, "\n");
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
/*
** Obtient le mode dans lequel va se lancer l'autocomp.
** 0 = rien n'est écrit il faut chercher dans le dossier courant.
** 1 = rien n'est écrit il faut chercher dans les binaires.
** 2 = le début est écrit, il faut chercher dans le dossier ou compléter le PATH.
** 3 = le début est écrit il faut chercher dans les binanires.
*/
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
	int			len;
	int			mode;

	len = 0;
	if (COMP_STATE == 1)
		ft_state_one(stream);
	else if (COMP_STATE == 2)
		ft_state_two(stream);
	else
	{
		reset_autocomp(stream);
		if (stream->command)
		{
			while (!ft_is_separator(stream->command[stream->pos])
				&& stream->command[stream->pos])
				ft_mvright(stream);
			COMP_BEGIN = ft_strsub(get_begin(stream->pos - 1,
					stream->command,  &len), 0, len);
			mode = get_mode(len, stream->command, stream);
			build_list(COMP_BEGIN, mode, stream);
			if (COMP_BEGIN_LIST)
				COMP_STATE = 1;
		}
	}
	if (COMP_BEGIN_LIST)
		ft_underline_mess(NULL, stream);
}

