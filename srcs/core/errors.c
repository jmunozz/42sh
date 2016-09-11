/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:54 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 19:55:57 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_initerror(t_config *config)
{
	ft_free_config(config);
	ft_putstr_fd("minishell: init error\n", 2);
	return (1);
}

int		ft_malloc_error(char const *path)
{
	ft_putstr_str_str_fd("minishell: malloc error: ", (char *)path, "\n", 2);
	ft_status(1);
	return (0);
}

void	ft_lexer_error(char *command)
{
	ft_putstr_str_str_fd("minishell: lexer error: ", command, "\n", 2);
	free(command);
	ft_status(1);
}

void	ft_fork_error(void)
{
	ft_status(1);
	ft_putstr_fd("minishell: forking error\n", 2);
}

void	ft_term_error(t_config *config)
{
	ft_status(1);
	ft_putstr_fd("minishell: unable to get terminal, default ansi code will", 2);
	ft_putstr_fd(" be use, be aware display problem may occur\n", 2);
	config->term_state = 0;
}
