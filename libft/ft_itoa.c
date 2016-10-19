/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:32:11 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:09:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_countnbsize(int n)
{
	size_t	size;

	size = 1;
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	if (n < 0)
		size++;
	return (size);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		limit;
	int		size;

	limit = 0;
	if (n < 0)
		limit = 1;
	size = (int)ft_countnbsize(n);
	str = ft_strnew((size_t)size);
	if (str)
	{
		while (--size >= limit)
		{
			if (limit == 0)
				str[size] = '0' + (n % 10);
			else
				str[size] = '0' + (-(n % 10));
			n /= 10;
		}
		if (limit == 1)
			str[size] = '-';
	}
	return (str);
}
