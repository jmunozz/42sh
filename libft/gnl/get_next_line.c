/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:30:52 by tboos             #+#    #+#             */
/*   Updated: 2016/02/25 06:30:24 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_free_line(t_line **begin, t_line *next)
{
	while ((*begin)->next != next)
		*begin = (*begin)->next;
	if (next == *begin)
	{
		free(next->data);
		free(next);
		*begin = NULL;
	}
	else
	{
		(*begin)->next = next->next;
		free(next->data);
		free(next);
	}
	return (1);
}

static int			ft_findread(t_line **begin, t_line *next, int fd, int mode)
{
	char			tmp[BUFF_SIZE + 1];
	int				ret;

	while (*begin && (*begin)->fd != fd && (*begin)->next != next)
		*begin = (*begin)->next;
	if (mode == FIND && (*begin) && (*begin)->fd == fd)
		return (1);
	if (!(ret = read(fd, tmp, BUFF_SIZE)))
		return (0);
	tmp[ret] = '\0';
	if (mode == READ && ft_strcpy((*begin)->data, tmp))
		return (ret);
	if (!(*begin) && !(*begin = MALLOC))
		return (-1);
	else if ((*begin)->fd != fd && !((*begin)->next = MALLOC))
		return (-1);
	if (next)
		*begin = (*begin)->next;
	(*begin)->data = ft_memcpy(ft_memalloc(BUFF_SIZE + 1), tmp, BUFF_SIZE);
	(*begin)->ret = ret;
	(*begin)->fd = fd;
	(*begin)->next = (next ? next : *begin);
	return (1);
}

static int			ft_strcut(char *src, int c, int ret)
{
	char	*tmp;

	tmp = src;
	while (ret--)
	{
		if (*tmp == c || *tmp == '\0')
		{
			*tmp = '\0';
			return (tmp - src + 1);
		}
		tmp++;
	}
	*tmp = '\0';
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static t_line	*begin = NULL;
	int				test;
	char			*tmp;

	test = -1;
	if (fd < 0 || !line || read(fd, *line, 0) < 0
		|| (test = ft_findread(&begin, begin, fd, FIND)) <= 0)
		return ((fd < 0 ? -1 : test));
	*line = ft_memalloc(1);
	while (*line && !(test = ft_strcut(DATA, '\n', RET))
		&& (tmp = *line)
		&& (*line = ft_strjoin(*line, DATA))
		&& (RET = ft_findread(&begin, begin, fd, READ)))
		free(tmp);
	if (!(*line))
		return (-1);
	if (RET && test)
	{
		tmp = *line;
		*line = ft_strjoin(*line, DATA);
		free(tmp);
		RET = RET - test;
		DATA = ft_strncpy(DATA, DATA + test, RET);
	}
	return ((RET ? 1 : ft_free_line(&begin, begin)));
}
