/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:00:36 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 12:23:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_printbits(void *content, size_t size_content)
{
	int		i;
	int		n;

	n = (int)size_content;
	if (content && size_content > 0)
		while (--n >= 0)
		{
			i = 8;
			while (--i >= 0)
				if (((unsigned char *)content)[n] & (1 << i))
					ft_putchar('1');
				else
					ft_putchar('0');
		}
}
