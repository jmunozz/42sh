/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 14:59:00 by maxpetit          #+#    #+#             */
/*   Updated: 2016/10/17 17:00:37 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "globing.h"

void	ft_star(char *str, t_glob *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] == 42 && ++j)
		i++;
	if (str[i] == 47)
	{
		if (j > 1)
			data->recursive = 1;
		i++;
	}
	while (str[i] == 42)
		i++;
	while (str[i] && (str[i] != 32))
		len++;
}

void	ft_parser(char *str)
{
	t_glob	data;
	char	*tmp;

	data.recursive = 0;
	tmp = str;
	while (*tmp)
	{
		if (*tmp == 42)
			ft_star(tmp);
		if (*tmp == 92)
			printf("WAZA1");
		tmp++;
	}
}

int main(int ac, char **av)
{

	if (ac == 2)
		ft_parser(av[1]);
	return (0);
}
