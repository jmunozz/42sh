/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 20:43:00 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		minishell.c_lflag &= ~ECHO;
*/

int		ft_termios_handle(int mode)
{
	struct termios	minishell;
	static char		state = 'n';

	if (mode && state == 'n')
	{
		if (tcgetattr(STDIN_FILENO, &termios_backup))
			return (1);
		if (!ft_memcpy(&minishell, &termios_backup, sizeof(struct termios)))
			return (1);
		minishell.c_iflag |= BRKINT;
		minishell.c_lflag |= (ICANON | ECHOE | ECHOK | ECHONL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &minishell))
			return (1);
		state = 'y';
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
	return (1);
}

char	*ft_streamscan(t_config *config, int fd)
{
	char			*command;

dprintf(1, "scanning \n");
	if (config)
		ft_termios_handle(1);
	if (get_next_line(fd, &command) < 0)
	{
		ft_putstr_fd("minishell: error while scanning command", 2);
		return (NULL);
	}
	return (command);
}
