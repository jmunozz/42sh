/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 16:37:59 by tboos             #+#    #+#             */
/*   Updated: 2016/11/04 17:22:32 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_prompt(t_config *config)
{
	if (!config->heredoc)
	{
		if (!config->last_exit)
			ft_putstr("\x1b[34m-> \x1b[1;32m");
		else
			ft_putstr("\x1b[31m-> \x1b[1;32m");
	}
	ft_putstr(config->pwd_subrep);
	if (!config->heredoc)
		ft_putstr(" : \x1b[0m");
}
