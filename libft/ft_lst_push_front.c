/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:47:00 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/30 16:45:30 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lst_push_front(t_list **begin_list, void *data, size_t content_size)
{
	t_list	*new_node;

	new_node = NULL;
	if (begin_list)
	{
		new_node = ft_lstnew(data, content_size);
		new_node->next = *begin_list;
		*begin_list = new_node;
	}
}
