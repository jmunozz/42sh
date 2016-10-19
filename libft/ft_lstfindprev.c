/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindprev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:19:12 by rbaran            #+#    #+#             */
/*   Updated: 2016/06/01 17:19:55 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstfindprev(t_list **begin_list, t_list **elem)
{
	t_list *buf;

	if (begin_list)
	{
		buf = *begin_list;
		while (buf)
		{
			if (buf->next == *elem)
				return (buf);
			buf = buf->next;
		}
	}
	return (NULL);
}
