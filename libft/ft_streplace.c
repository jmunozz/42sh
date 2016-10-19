/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streplace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:18:40 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 12:29:24 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_streplace(char *str, char const pattern, char const c)
{
	char	*begin_str;

	if (!str)
		return (NULL);
	begin_str = str;
	while (*str != '\0')
	{
		if (*str == pattern)
			*str = c;
		str++;
	}
	return (begin_str);
}
