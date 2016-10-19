/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 10:41:22 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:11:21 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void	*memalloc;

	memalloc = malloc(sizeof(*memalloc) * size);
	if (memalloc)
		ft_bzero(memalloc, size);
	return (memalloc);
}
