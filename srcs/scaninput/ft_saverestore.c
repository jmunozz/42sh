/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saverestore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:30:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/05 16:35:53 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_savecursor(void)
{
	char *res;

	if ((res = tgetstr("sc", NULL)))
		tputs(res, 0, &ft_putchar_int);
}

void	ft_restorecursor(void)
{
	char *res;

	if ((res = tgetstr("rc", NULL)))
		tputs(res, 0, &ft_putchar_int);
}
