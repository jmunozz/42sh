/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:30:28 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strtabnew(char *s)
{
	char	**t;

	if (!*s || !(t = (char **)ft_memalloc(sizeof(char *) * 2)))
		return NULL;
	if (!(*t = ft_strdup(s)) && ft_freegiveone((void *)&t))
		return NULL;
	return (t);
}

static char	**sft_tabdup(char **t, char *m, char c, int nb)
{
	int		i;

	i = 0;
	while (nb--)
	{
		if (!(t[i++] = ft_strdup(m)))
		{
			ft_strtabfree(t);
			return NULL;
		}
		else if (nb)
		{
			m += ft_strlen(m) + 1;
			while (*m == c)
				m++;
		}
	}
	return (t);
}

char		**ft_strsplit(char *s, char c)
{
	char	**t;
	char	*m;
	int		nb;

	if (!c)
		return (ft_strtabnew(s));
	while (*s == c)
		++s;
	if (!(*s))
		return NULL;
	m = s;
	nb = 0;
	while (*(++s))
		if (*s == c && *(s - 1) && *(s - 1) != c && !(*s = 0) && ++s)
			nb++;
	nb += (*(s - 1) != c ? 1 : 0);
	if (!(t = (char **)ft_memalloc(sizeof(char *) * (nb + 1))))
		return NULL;
	return (sft_tabdup(t, m, c, nb));
}
