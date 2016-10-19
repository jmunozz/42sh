/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/02 11:23:33 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 12:30:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*ft_convert_final(int nb, char *base_to)
{
	int		base;
	int		i;
	int		i2;
	char	*str;

	base = ft_strlen(base_to);
	i2 = nb;
	i = 0;
	while (i2)
	{
		i2 /= base;
		i++;
	}
	str = (char*)malloc(sizeof(str) * (i + 1));
	if (str)
	{
		str[i] = '\0';
		while (--i >= 0)
		{
			str[i] = base_to[nb % base];
			nb /= base;
		}
	}
	return (str);
}

static int	ft_convertstr(char *str, char *base_from)
{
	int		i;
	int		i2;
	int		coef;
	int		ibasefrom;
	int		nb_str;

	i = 0;
	i2 = 0;
	nb_str = 0;
	i2 = ft_strlen(str) + 1;
	while (str[i] != '\0')
	{
		coef = 1;
		while (--i2 > 1)
			coef *= ft_strlen(base_from);
		ibasefrom = 0;
		while (str[i] != base_from[ibasefrom])
			ibasefrom++;
		nb_str += ibasefrom * coef;
		i++;
		i2 = ft_strlen(str) + 1 - i;
	}
	return (nb_str);
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*str;

	str = NULL;
	if (ft_convertstr(nbr, base_from) == 0)
	{
		str = (char*)malloc(sizeof(*str) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	return (ft_convert_final(ft_convertstr(nbr, base_from), base_to));
}
