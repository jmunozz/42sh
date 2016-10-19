/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 12:37:15 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/13 12:52:37 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_findindxstart(char const *s, char c)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == c)
		i++;
	return (i);
}

static int	ft_findindxlast(char const *s, char c)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	ft_countwords(char const *s, char c)
{
	unsigned int	boolean;
	int				words_nb;

	if (!s)
		return (0);
	boolean = 0;
	words_nb = 0;
	while (*s != '\0')
	{
		if (*s == c)
			boolean = 0;
		else if (boolean == 0)
		{
			words_nb++;
			boolean = 1;
		}
		s++;
	}
	return (words_nb);
}

static void	ft_fillstrsplit(char const *s, char **tab, char c, int tab_len)
{
	int				i;
	unsigned int	idxstart;
	unsigned int	idxlast;

	i = 0;
	idxstart = 0;
	idxlast = 0;
	while (i < tab_len)
	{
		idxstart = ft_findindxstart(s + idxlast, c) + idxlast;
		idxlast = ft_findindxlast(s + idxstart, c) + idxstart;
		tab[i] = (char*)malloc(sizeof(*tab) * (idxlast - idxstart + 1));
		if (tab[i])
		{
			tab[i] = ft_strncpy(tab[i], s + idxstart, idxlast - idxstart);
			tab[i][idxlast - idxstart] = '\0';
		}
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		tab_len;

	if (!s)
		return (NULL);
	tab_len = ft_countwords(s, c);
	tab = (char**)malloc(sizeof(*tab) * (tab_len + 1));
	if (tab)
	{
		tab[tab_len] = NULL;
		ft_fillstrsplit(s, tab, c, tab_len);
	}
	return (tab);
}
