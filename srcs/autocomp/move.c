/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:42 by tboos             #+#    #+#             */
/*   Updated: 2016/10/14 18:13:36 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/autocomp.h"

void		ft_comp_get_left(t_stream *stream)
{
	if (COMP_CURRENT >= COMP_IN_COL)
		COMP_CURRENT -= COMP_IN_COL;
}

void		ft_comp_get_right(t_stream *stream)
{
	size_t	min;

	if (COMP_SIZE_LIST % COMP_IN_COL == 0)
		min = COMP_SIZE_LIST - COMP_IN_COL;
	else
		min = COMP_SIZE_LIST - (COMP_SIZE_LIST % COMP_IN_COL);
	if (COMP_CURRENT < COMP_SIZE_LIST && COMP_CURRENT >= min)
		;
	else
		COMP_CURRENT += COMP_IN_COL;
}

void		ft_comp_get_up(t_stream *stream)
{
	if (COMP_CURRENT == 0)
		COMP_CURRENT = COMP_SIZE_LIST - 1;
	else
		COMP_CURRENT -= 1;
}

void		ft_comp_get_down(t_stream *stream)
{
	if (COMP_CURRENT == COMP_SIZE_LIST - 1)
		COMP_CURRENT = 0;
	else
		COMP_CURRENT += 1;
}

void		ft_state_one(t_stream *stream)
{
	COMP_CURRENT = 0;
	ft_comp_select_current(COMP_CURRENT, stream, 'S');
	COMP_STATE = 2;
}

void		ft_state_two(t_stream *stream)
{
	size_t current_tmp;

	current_tmp = COMP_CURRENT;
	if (((ssize_t *)(stream->buf))[0] == CHT)
		ft_comp_get_down(stream);
	else if (((ssize_t *)(stream->buf))[0] == LEF)
		ft_comp_get_left(stream);
	else if (((ssize_t *)(stream->buf))[0] == RIG)
		ft_comp_get_right(stream);
	else if (((ssize_t *)(stream->buf))[0] == UPP)
		ft_comp_get_up(stream);
	else if (((ssize_t *)(stream->buf))[0] == DOW)
		ft_comp_get_down(stream);
	ft_comp_select_current(current_tmp, stream, 'U');
	ft_comp_select_current(COMP_CURRENT, stream, 'S');

}

void		ft_comp_select_current(size_t current, t_stream *stream, char mode)
{
	t_list	*list;
	size_t	i;

	list = COMP_BEGIN_LIST;
	i = -1;
	while (++i < current && list)
		list = list->next;
	bzero(stream->buf, 256);
	ft_strcpy(stream->buf, (char*)list->data);
	if (mode == 'S')
		list->data_size = 1;
	else
		list->data_size = 0;
}
