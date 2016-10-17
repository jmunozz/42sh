/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_r_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 17:39:53 by rbaran            #+#    #+#             */
/*   Updated: 2016/09/28 17:50:12 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*ft_build_r_pipe(t_list *begin, t_config *config)
{
	int		*pip;

	pip = NULL;
	while (begin)
	{
		if (begin->data_size && (ft_strncmp((char *)(begin->data), "<", 1))
			&& ft_strncmp((char *)(begin->data), ">", 1))
			break ;
		if (begin->data_size && !ft_strncmp((char *)(begin->data), "<", 1))
		{
			if (!(pip = (int *)ft_memalloc(sizeof(int) * 2)))
				return (ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR));
			if (-1 == pipe(pip))
				return (ft_error(SHNAME, "parser", "pipe error", CR_ERROR));

			ft_agregate(begin, pip, tmp, config);
		}
		begin = begin->next;
	}
	return (pip);
}
