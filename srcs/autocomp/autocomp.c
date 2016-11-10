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
/*
** Permet de définir COMP_BEGIN (moyennant intervention de ft_strsub) qui
** représente le début de la chaîne à comparer. COMP_BEGIN est modifié dans
** build_list.c dans le cas où on chercher à compléter un chemin.
*/
char	*get_begin(int i, char *str, int *len)
{
	while (i >= 0 && !ft_is_separator(str[i]))
	{
		i -= 1;
		*len += 1;
	}
	return (&(str[++i]));
}
/*
** Fonction principale d'exécution de l'autocomp.
** Lance les différents comportements en fonction de COMP_STATE.
** Si COMP_SIZE_LIST = 1, modifie directement la ligne de commande.
** Sinon imprime la liste en colonnes.
*/
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
	if (COMP_SIZE_LIST == 1)
	{
		ft_comp_select_current(0, stream, 'S');
		ft_autocomp_append(stream);
		COMP_STATE = 0;
	}
	else if (COMP_BEGIN_LIST)
		ft_underline_mess(NULL, stream);
}

