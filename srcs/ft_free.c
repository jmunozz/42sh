/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 11:03:31 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 11:56:56 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_free_split(char **split)
{
	while (split && *split)
	{
		if (*split)
			free(*split);
		split++;
	}
	free(*split);
}

void	ft_free_bin(t_bin **bin)
{
	t_bin *bin_buf;

	while (*bin)
	{
		bin_buf = *bin;
		*bin = (*bin)->next;
		free(bin_buf->name);
		free(bin_buf->path);
		free(bin_buf);
	}
}
