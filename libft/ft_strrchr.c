/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 21:01:26 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:18:43 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	int		length;

	length = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + length);
	while (--length >= 0)
		if (s[length] == c)
			return (((char *)s) + length);
	return (NULL);
}
