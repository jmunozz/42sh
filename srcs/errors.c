/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:54 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 21:17:55 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_malloc_error(char const *path)
{
	ft_putstr_str_str_fd("minishell: malloc error: ", (char *)path, "\n",2);
	ft_status(1);
	return (0);
}

void	ft_lexer_error(char *command)
{
	ft_putstr_str_str_fd("minishell: lexer error: ", command, "\n",2);
	free(command);
	ft_status(1);
}

int		ft_prompt_error(void)
{
	ft_status(1);
	ft_putendl_fd("minishell: error searching pwd for prompt", 2);
	ft_putstr("\x1b[34m-> \x1b[1;32mLove you anyway : \xb1[0m");
	return (1);
}

void	ft_fork_error(void)
{
	ft_status(1);
	ft_putstr_fd("minishell: forking error", 2);
}
