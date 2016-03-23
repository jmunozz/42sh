/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 21:22:41 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void		ft_minishell(t_config *config)
{
	char	*command;
	char	**argv;
	pid_t	father;
	int		stat_loc;

	stat_loc = 0;
	while (ft_prompt(config) && (command = ft_streamscan(config)))
	{
		if (!(argv = ft_strsplit(command, ' ')))
			ft_lexer_error(command);
		else if (ft_freegiveone((void **)&command)
				&& (command = ft_return_binpath(config, argv[0])))
		{
			free(argv[0]);
			argv[0] = command;
			ft_putchar('\n');
			if (-1 > (father = fork()))
				ft_fork_error();
			else if (father == 0)
				execve(command, argv, config->env);
			else if (father !=  0)
				waitpid(father, &stat_loc, 0);
		}
		else
			ft_putstr_fd("no such exe in path !\n", 2);
	}
	ft_putchar('\n');
	ft_free_config(config);
}
