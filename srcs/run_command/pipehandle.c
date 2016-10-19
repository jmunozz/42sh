/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:13:28 by rbaran            #+#    #+#             */
/*   Updated: 2016/10/19 13:21:15 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redirectpipe(t_list *begin, int *pip, t_config *config,
			char *tmp)
{
	int	flags;
	int	fd;

	flags = 0;
	fd = -1;
	if ((!begin->next || !tmp)
		&& ft_error(SHNAME, "parser", "redirection error", CR_ERROR))
		return (1);
	if (!ft_strcmp(tmp, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (!ft_strcmp(tmp, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (!ft_strcmp(tmp, "<"))
		flags = O_RDONLY;
	ft_quote_handle(&(begin->next), config);
	if ((fd = open(((char**)begin->next->data)[0], flags,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1
		&& ft_error(SHNAME, ((char**)begin->next->data)[0],
		"file does not exist", CR_ERROR))
		return (1);
	(flags == O_RDONLY) ? dup2(fd, pip[0]) : dup2(fd, pip[1]);
	close(fd);
	return (0);
}

static void	ft_agregate(t_list *begin, int *pip, char *tmp, t_config *config)
{
	t_list	*kill;

	if (!ft_strncmp(tmp, "|", 1) && ft_freegiveone((void**)&(tmp)))
		return ;
	if (!ft_strncmp(tmp, ">", 1) && ft_redirectpipe(begin, pip, config, tmp))
		return ;
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

static int	ft_newpipe(int **pip)
{
	if (!(*pip = (int *)ft_memalloc(sizeof(int) * 2)))
		return (ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR));
	if (-1 == pipe(*pip))
		return (ft_error(SHNAME, "parser", "pipe error", CR_ERROR));
	return (0);
}

static int	ft_build_r_pipe(t_list **begin, t_config *config, int **r_pipe)
{
	t_list	*kill;

	if (!*r_pipe && ft_newpipe(r_pipe))
		return (1);
	if (ft_redirectpipe((*begin)->next, *r_pipe, config, (*begin)->next->data))
		return (1);
	if ((*begin)->next->next)
	{
		kill = (*begin)->next;
		(*begin)->next = (*begin)->next->next;
		ft_freegiveone((void**)&(kill->data));
		ft_freegiveone((void**)&kill);
		if ((*begin)->next)
		{
			kill = (*begin)->next;
			(*begin)->next = (*begin)->next->next;
			ft_strtabfree((char**)(kill->data));
			ft_freegiveone((void**)&kill);
		}
	}
	return (0);
}

int			ft_build_pipe(t_list *begin, t_config *config, int **r_pipe)
{
	int		*pip;
	char	*tmp;

	tmp = NULL;
	while (begin)
	{
		if (begin->next && begin->next->data_size
			&& !ft_strcmp((char *)(begin->next->data), "<")
			&& ft_build_r_pipe(&begin, config, r_pipe))
			return (1);
		else if (begin->data_size && (!ft_strcmp((char *)(begin->data), "|")
			|| !ft_strncmp((char *)(begin->data), ">", 1)))
		{
			if (ft_newpipe(&pip))
				return (1);
			tmp = (char*)begin->data;
			begin->data_size = PIPE;
			begin->data = (void*)pip;
			break ;
		}
		else
			begin = begin->next;
	}
	if (begin && begin->data_size == PIPE)
		ft_agregate(begin, pip, tmp, config);
	return (0);
}
