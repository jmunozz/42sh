/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 21:12:43 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:18:29 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *s, const char *needle, size_t n)
{
	size_t			i;

	i = 0;
	while (n > 0 && *s != '\0')
	{
		while (s[i] == needle[i] && needle[i] != '\0' && s[i] != '\0' && i < n)
			i++;
		if (needle[i] == '\0')
			return ((char *)s);
		else
			i = 0;
		s++;
		n--;
	}
	if (needle[i] == '\0')
		return ((char *)s - i);
	return (NULL);
}
