/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:03:06 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:10:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*turtle;
	t_list	*begin_new_lst;

	new_lst = NULL;
	turtle = NULL;
	begin_new_lst = NULL;
	while (lst)
	{
		new_lst = f(ft_lstnew(lst->content, lst->content_size));
		if (!new_lst)
			return (new_lst);
		if (!begin_new_lst)
			begin_new_lst = new_lst;
		else
			turtle->next = new_lst;
		turtle = new_lst;
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (begin_new_lst);
}
