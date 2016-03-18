/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/03/18 18:11:50 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_minishell(t_config *config)
{
	/*
	pid_t	father;
	char	**command;

	while (command = ft_streamscan())
	{
		if (ft_builin(config, command))
			ft_strtabfree(command);
		else if (-1 > (father = fork()))
			return (ft_fork_error(config, command));
		else if (father == 0)
			ft_execve(config, command);
		else if (father !=  0)
			ft_waitforson(father);
		ft_putstr(config->prompt);
	}
	return (ft_prompt_error(config));
	*/
	ft_free_config(config);
	ft_putstr("on est bon");
}
