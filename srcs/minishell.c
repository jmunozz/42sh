/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 17:58:43 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_minishell(t_config *config)
{
	char	*command;
	char	**argv;

	while (ft_prompt(config) && (command = ft_streamscan(config)))
	{
		argv = ft_strsplit(command, ' ');
		free(command);
		command
		ft_putchar('\n');
		if (-1 > (father = fork()))
			return (ft_fork_error(config, command));
		else if (father == 0)
			ft_execve(config, command);
		else if (father !=  0)
			ft_waitforson(father);
	}
	ft_putchar('\n');
	ft_free_config(config);
}
