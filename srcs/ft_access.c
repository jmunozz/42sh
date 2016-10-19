/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 14:43:47 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:24:11 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_accessdir(char *path)
{
	struct stat	stats;

	if (stat(path, &stats))
	{
		ft_error(path, "stat does not work :/, can't check type of file", KEEP);
		return (0);
	}
	if (!(S_ISDIR(stats.st_mode)))
	{
		ft_error(path, FILE_NOTDIR, KEEP);
		return (0);
	}
	return (1);
}

int			ft_access(char *path, int type)
{
	if (access(path, F_OK) == -1)
	{
		ft_error(path, FILE_NOTFOUND, KEEP);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		ft_error(path, FILE_PERMDENIED, KEEP);
		return (0);
	}
	return (type ? ft_accessdir(path) : 1);
}
