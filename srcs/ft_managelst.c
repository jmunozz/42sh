/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_managelst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 09:36:37 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/02 10:51:51 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

t_bin	*ft_findlast(t_bin *begin_lst)
{
	while (begin_lst && begin_lst->next)
		begin_lst = begin_lst->next;
	return (begin_lst);
}
