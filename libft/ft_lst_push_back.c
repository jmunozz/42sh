/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:57:00 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/30 16:46:46 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lst_push_back(t_list **begin_list, void *data, size_t content_size)
{
	t_list	*list;

	list = NULL;
	if (begin_list)
	{
		if (*begin_list)
		{
			list = *begin_list;
			while (list->next != NULL)
				list = list->next;
			list->next = ft_lstnew(data, content_size);
		}
		else
			*begin_list = ft_lstnew(data, content_size);
	}
}
