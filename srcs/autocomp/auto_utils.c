/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:57 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 13:15:29 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_isspace(c))
		return (1);
	return (0);
}
/*
 ** Permet de définir COMP_BEGIN (moyennant intervention de ft_strsub) qui
 ** représente le début de la chaîne à comparer. COMP_BEGIN est modifié dans
 ** build_list.c dans le cas où on chercher à compléter un chemin.
 */
char	*get_begin(int i, char *str, size_t *len)
{
	while (i >= 0 && !ft_is_separator(str[i]))
	{
		i -= 1;
		*len += 1;
	}
	return (str + i + 1);
}
