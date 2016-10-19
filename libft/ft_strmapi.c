/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 11:00:19 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:17:28 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	length;
	unsigned int	i;

	if (!s || !f)
		return ((char*)s);
	length = ft_strlen(s);
	i = 0;
	str = (char*)malloc(sizeof(*str) * (length + 1));
	if (str)
	{
		str[length] = '\0';
		while (*s != '\0')
		{
			str[i] = f(i, *s);
			s++;
			i++;
		}
	}
	return (str);
}
