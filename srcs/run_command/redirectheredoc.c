/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectheredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:15:36 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/04 17:19:45 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirectheredoc(t_list *begin, int **r_pipe)
{
	int		i;
	
	close((*r_pipe)[0]);
	close((*r_pipe)[1]);
	if (pipe(*r_pipe) == -1)
		return (ft_error(SHNAME, "parser", "pipe heredoc error", CR_ERROR));
	i = 0;
	while (((char**)(begin->data))[++i])
	{
		write((*r_pipe)[1], ((char**)(begin->data))[i],
				ft_strlen(((char**)(begin->data))[i]));
		write((*r_pipe)[1], "\n", 1);
	}
	return (0);
}
