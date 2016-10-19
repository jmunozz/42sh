/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 11:00:19 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:17:19 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
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
			str[i] = f(*s);
			s++;
			i++;
		}
	}
	return (str);
}
