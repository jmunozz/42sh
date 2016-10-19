/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 21:12:43 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:19:02 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *s, const char *needle)
{
	unsigned int	i;

	i = 0;
	while (*s != '\0')
	{
		while (s[i] == needle[i] && s[i] != '\0' && needle[i] != '\0')
			i++;
		if (needle[i] == '\0')
			return ((char *)s);
		else
			i = 0;
		s++;
	}
	if (needle[i] == '\0')
		return ((char *)s - i);
	return (NULL);
}
