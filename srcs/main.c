/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:26:22 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		minishell.c_lflag &= ~ECHO;
*/

int		ft_termios_handle(int mode)
{
	struct termios			minishell;

	if (mode)
	{
		if (SIG_ERR == signal(SIGINT, SIG_IGN))
			return (ft_initerror());
		if (SIG_ERR == signal(SIGTSTP, SIG_IGN))
			return (ft_initerror());
		if (tcgetattr(STDIN_FILENO, &termios_backup))
			return (ft_initerror());
		if (!ft_memcpy(&minishell, &termios_backup, sizeof(struct termios)))
			return (ft_initerror());
		minishell.c_iflag |= BRKINT;
		minishell.c_lflag |= (ICANON | ECHOE | ECHOK | ECHONL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &minishell))
			return (ft_initerror());
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_config				*config;

	if (ac)
		(void)av;
	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
		return (ft_initerror());
	config->bin = NULL;
	ft_bzero(config->history, sizeof(config->history));
	if (!(config->env = ft_strtabdup(env))
		|| !ft_pathtohash(config))
	{
		ft_free_config(config);
		return (ft_initerror());
	}
	if (!ft_termios_handle(1))
		ft_minishell(config);
	ft_free_config(config);
	ft_termios_handle(0);
	return (ft_status(0));
}
