/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:13:28 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/04 17:12:00 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_newpipe(int mode)
{
	int		*pip;
	t_list	*new;

	if (!(pip = (int *)ft_memalloc(sizeof(int) * 2))
		&& ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR))
		return (NULL);
	if (-1 == pipe(pip) && ft_error(SHNAME, "parser", "pipe error", CR_ERROR)
		&& ft_freegiveone((void**)pip))
		return (NULL);
	if (mode)
	{
		if (!(new = (t_list*)ft_memalloc(sizeof(t_list)))
			&& ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR))
			return (NULL);
		new->data_size = PIPE;
		new->data = pip;
		return ((void*)new);
	}
	return ((void*)pip);
}

static int	ft_redirectheredoc(t_list *begin, t_list **rhead, t_config *config,
		int **r_pipe)
{
	int		i;
	
	close((*r_pipe)[0]);
	close((*r_pipe)[1]);
	if (pipe(*r_pipe) == -1)
		return (1 ^ ft_error(SHNAME, "parser", "pipe heredoc error", CR_ERROR));
	i = 0;
	while (((char**)((*rhead)->next->data))[++i])
	{
		write((*r_pipe)[1], ((char**)((*rhead)->next->data))[i],
				ft_strlen(((char**)((*rhead)->next->data))[i]));
		write((*r_pipe)[1], "\n", 1);
	}
dprintf(1, "heredoc ok\n");
	return (ft_node_descriptors(begin, rhead, config, r_pipe));
}

static int	ft_agregate(t_list *begin, t_list **rhead, t_config *config,
			int **r_pipe)
{
	int		flags;
	int		fd;
	char	*tmp;
	int		*pip;

	tmp = (char*)(*rhead)->data;
	pip = (tmp[0] == '>' ? (int*)begin->next->data : *r_pipe);
	if (!(*rhead)->next)
		return (1 ^ ft_error(SHNAME, "parse error near", tmp, CR_ERROR));
	if (!ft_strcmp(tmp, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (!ft_strcmp(tmp, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_RDONLY;
	ft_quote_handle((*rhead)->next, config);
	tmp = ((char**)(*rhead)->next->data)[0];
	if ((fd = open(tmp, flags, OFG) == -1))
		return (1 ^ ft_error(SHNAME, tmp, "file does not exist", CR_ERROR));
	if (-1 == ((flags == O_RDONLY) ? dup2(fd, pip[0]) : dup2(fd, pip[1])))
		return (1 ^ ft_error(SHNAME, "parser", "dup error", CR_ERROR));
	close(fd);
dprintf(1, "agregation ok\n");
	return (ft_node_descriptors(begin, rhead, config, r_pipe));
}

int			ft_node_descriptors(t_list *begin, t_list **rhead, t_config *config,
		int **r_pipe)
{
	char	tmp;

	if (begin->next == *rhead)
		begin->next = NULL;
	else
		*rhead = ft_partial_freelist(*rhead, 2);
	if (*rhead)
	{
		tmp = ((char*)(*rhead)->data)[0];
		if ((tmp == '|' || tmp == '>')
			&& !begin->next && !(begin->next = ft_newpipe(1)))
			return (0);
		if (tmp == '<' && !*r_pipe && !(*r_pipe = ft_newpipe(0)))
			return (0);
		if (!ft_strcmp((*rhead)->data, "<<"))
			return (ft_redirectheredoc(begin, rhead, config, r_pipe));
		if (tmp == '<' || tmp == '>')
			return (ft_agregate(begin, rhead, config, r_pipe));
		if (tmp == '|')
			*rhead = ft_partial_freelist(*rhead, 1);
	}
	return (1);
}

int			ft_build_pipe(t_list *begin, t_config *config, int **r_pipe)
{
	t_list	*rhead;

	while (begin && begin->data_size && begin->data_size != SSHELL)
		begin = begin->next;
	if (begin && begin->next)
	{
		rhead = begin->next;
		if (!ft_node_descriptors(begin, &rhead, config, r_pipe))
			return (0);
		if (begin->next)
			begin->next->next = rhead;
		else
			begin->next = rhead;
	}
dprintf(1,"LIST = \n");
ft_lstiter(begin, ft_print_list);
dprintf(1,"FIN LIST\n");
	return (1);
}
