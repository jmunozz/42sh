/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 16:18:49 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 15:41:06 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

t_bin	*ft_findcmd(char *cmd, t_bin *cmds)
{
	while (cmds)
	{
		if (!ft_strcmp(cmds->name, cmd))
			return (cmds);
		cmds = cmds->next;
	}
	return (NULL);
}
