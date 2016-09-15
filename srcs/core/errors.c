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

int		ft_error(char *name, char *other, char *mess, int mode)
{
	if (mode & FCR_ERROR)
		ft_putchar_fd('\n', 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (other)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (mess)
		ft_putstr_fd(name, 2);
	if (mode & CR_ERROR)
		ft_putchar_fd('\n', 2);
	if (mode & SERROR)
		ft_status(1);
	return true;
}

int		ft_initerror(t_config *config)
{
	ft_free_config(config);
	ft_error(SHNAME, NULL, "init error", CR_ERROR);
	return (1);
}

void	ft_lexer_error(char *command)
{
	ft_error(SHNAME, "lexer error", command, CR_ERROR | SERROR);
	free(command);
}

void	ft_term_error(t_config *config)
{
	ft_error(SHNAME, ANSI_USE, BEAWARE_ERR, CR_ERROR);
	config->term_state = 0;
}
