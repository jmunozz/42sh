/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:01:04 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 15:41:31 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

t_bin		*ft_hashsearch(t_conf *config, char *cmd)
{
	int	i;

	i = 0;
	while (config->hashtable[i])
	{
		if ((config->hashtable[i])->name[0] == *cmd)
			return (config->hashtable[i]);
		i++;
	}
	return (NULL);
}

void		ft_hashtable(t_conf *config)
{
	char	letter;
	t_bin	*bin;
	int		i;

	bin = config->bin;
	letter = -1;
	i = 0;
	while (bin)
	{
		if (letter != bin->name[0])
		{
			letter = bin->name[0];
			config->hashtable[i] = bin;
			i++;
		}
		bin = bin->next;
	}
}
