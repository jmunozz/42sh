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

char		**ft_strsplit(char *s, char c)
{
	char	*t;
	char	**r;
	int		nb;
	int		i;

	if (!s || !*s || !c)
		return (NULL);
	while (*s == c)
		s++;
	t = s;
	nb = 0;
	while (*s)
		if (s++ && *(s - 1) != c && ((*s == c && !(*s = '\0') && s++) || !*s))
			nb++;
	if (!nb || !(r = (char **)ft_memalloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	i = -1;
	while (++i < nb && (r[i] = ft_strdup(t))
		&& (t = t + ft_strlen(t) + 1))
		while (*t == c)
			t++;
	return (r);
}
