/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:13:28 by rbaran            #+#    #+#             */
/*   Updated: 2016/10/17 12:57:43 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirectpipe(t_list *begin, int *pip, t_config *config, char *tmp)
{
	int	flags;
	int	fd;

	flags = 0;
	fd = -1;
	if ((!begin->next || !tmp) && ft_error(SHNAME, "parser", "redirection error", CR_ERROR))
	return ;
	if (!ft_strcmp(tmp, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (!ft_strcmp(tmp, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	ft_quote_handle(&(begin->next), config);
	if ((fd = open(((char**)begin->next->data)[0], flags,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1
		&& ft_error(SHNAME, "parser", "open error", CR_ERROR))
		return ;
	dup2(fd, pip[1]);
	close(fd);
}

void		ft_agregate(t_list *begin, int *pip, char *tmp, t_config *config)
{
	t_list	*kill;

	if (!ft_strncmp(tmp, "|", 1) && ft_freegiveone((void**)&(tmp)))
		return ;
	if (!ft_strncmp(tmp, ">", 1))
			ft_redirectpipe(begin, pip, config, tmp);
	if (begin->next && begin->next->data)
	{
		ft_freegiveone((void**)&(tmp));
		ft_strtabfree((char**)(begin->next->data));
		kill = begin->next;
		begin->next = begin->next->next;
		ft_freegiveone((void**)&(kill));
		if (begin->next)
		{
			tmp = (char*)(begin->next->data);
			kill = begin->next;
			begin->next = begin->next->next;
			ft_freegiveone((void**)&(kill));
			ft_agregate(begin, pip, tmp, config);
		}
	}
}
