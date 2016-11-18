/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:16:50 by jmunoz            #+#    #+#             */
/*   Updated: 2016/11/18 13:11:01 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** Récupère la ligne de l'env correspondante à *str.
*/
int			ft_getenvline(char *str, char **e)
{
	int		i;

	i = 0;
	if (!e)
		return (-1);
	while (e[i])
	{
		if (!ft_strncmp(e[i], str, ft_strlenc(e[i], '=')) &&
				ft_strlenc(e[i], '=') == (int)ft_strlen(str))
			return (i);
		i++;
	}
	return (i);
}
/*
** Classe tous les éléments de la variable environnementale dans un tableau.
*/
char		**ft_getenvtab(char *str, char **e)
{
	int		i;
	char	*ret;

	if (!e)
		return (NULL);
	i = ft_getenvline(str, e);
	if (e[i] == NULL)
		return (NULL);
	ret = ft_strrchr(e[i], '=');
	if (ret)
		return (ft_strsplit(ret + 1, ':'));
	else
		return (ft_strsplit(e[i], ':'));
}
/*
** Récupère le nombre d'éléments par colonnes COMP_IN_COL.
*/
void		get_col_elem(t_stream *stream)
{
	size_t col_nb;
	col_nb = (COMP_COL + 1) / (COMP_PAD + 2);
	if (COMP_SIZE_LIST > col_nb)
		COMP_IN_COL = !(COMP_SIZE_LIST % col_nb) ? COMP_SIZE_LIST / col_nb : (COMP_SIZE_LIST / col_nb) + 1;
	else
		COMP_IN_COL = 1;
}
/*
** Lancée sur chaque chaîne, permet d'obtenir le padding de la plus grande.
*/
void		get_pad(t_stream *stream, char *str)
{
	size_t	size;

	if ((size = ft_strlen(str) + 1) > COMP_PAD)
		COMP_PAD = size;
}
/*
** Obtient la taille de la liste COMP_SIZE_LIST.
*/
void		get_size_list(t_stream *stream)
{
	t_list	*list;
	size_t	i;

	if (COMP_BEGIN_LIST)
	{
		i = 1;
		list = COMP_BEGIN_LIST;
		while (list->next)
		{
			i++;
			list = list->next;
		}
		COMP_SIZE_LIST = i;
	}
}
