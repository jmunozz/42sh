/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 21:22:40 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_streamscan(t_config *config)
{
	char			*command;
	char			*n_term;
	struct termios	term;

	if ((n_term = ft_strtabfind(config->env, "TERM")))
		if (tcgetattr(0, n_term)
	if (get_next_line(0, &command) <= 0)
		return(NULL);
	return (command);
}
