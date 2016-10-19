/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:28:52 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:11:09 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_lst;

	new_lst = (t_list*)malloc(sizeof(*new_lst));
	if (!new_lst)
		return (NULL);
	if (!content)
	{
		new_lst->content_size = 0;
		new_lst->content = NULL;
	}
	else
	{
		new_lst->content_size = content_size;
		new_lst->content = ft_memcpy(ft_memalloc(content_size), content,
				content_size);
	}
	new_lst->next = NULL;
	return (new_lst);
}
