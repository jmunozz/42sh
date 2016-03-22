/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 16:37:59 by tboos             #+#    #+#             */
/*   Updated: 2016/03/18 18:37:30 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_prompt(t_config *config)
{
	char	*pwd;
	char	*subrep;

	pwd = ft_strtabfind(config->env, "PWD");
	if (!pwd)
		return (0);
	ft_putstr("\x1b[34m-> \x1b[1;32m");
	if ((subrep = ft_strrchr(pwd, '/')))
		ft_putstr(subrep + 1);
	else
		ft_putstr(pwd + 4);
	ft_putstr(" : \x1b[0m");
	return (1);
}
