/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:16:50 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/07 16:19:19 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomp.h"

int			ft_getenvline(char *str, char **e)
{
	int		i;

	i = 0;
	if (!e)
		return (-1);
	while (e[i])
	{
		if (!ft_strncmp(e[i], str, ft_strlenc(e[i], '=')) &&
				ft_strlenc(e[i], '=') == (int)ft_strlen(str))
			return (i);
		i++;
	}
	return (i);
}

char		**ft_getenvtab(char *str, char **e)
{
	int		i;
	char	*ret;

	if (!e)
		return (NULL);
	i = ft_getenvline(str, e);
	if (e[i] == NULL)
		return (NULL);
	ret = ft_strrchr(e[i], '=');
	if (ret)
		return (ft_strsplit(ret + 1, ':'));
	else
		return (ft_strsplit(e[i], ':'));
}
