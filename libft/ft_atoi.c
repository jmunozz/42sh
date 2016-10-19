/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 22:11:28 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:08:35 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_atoi(const char *nptr)
{
	int		res;
	int		signe;

	res = 0;
	signe = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v' ||
		*nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		signe = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr <= '9' && *nptr >= '0')
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * signe);
}
