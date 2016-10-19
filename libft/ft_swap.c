/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:36:11 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 15:23:49 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_swap(void *content1, void *content2, size_t size)
{
	size_t			i;
	unsigned char	buf;

	if (content1 && content2)
	{
		i = 0;
		buf = 0;
		while (i < size)
		{
			buf = ((unsigned char *)content1)[i];
			((unsigned char *)content1)[i] = ((unsigned char *)content2)[i];
			((unsigned char *)content2)[i] = buf;
			i++;
		}
	}
}
