/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saverestore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:30:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:30:47 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_eraselines(void)
{
	char	*res_cd;
	char	*res_do;
	char	*res_cr;

	if ((res_do = tgetstr("do", NULL)))
	{
		tputs(res_do, 0, &ft_putchar_int);
		if ((res_cr = tgetstr("cr", NULL)))
		{
			tputs(res_cr, 0, &ft_putchar_int);
			if ((res_cd = tgetstr("cd", NULL)))
				tputs(res_cd, 0, &ft_putchar_int);
		}
	}
}

void		ft_erase(t_ctlinput *ctl)
{
	char	*res;

	res = tgetstr("ce", NULL);
	if (!res)
		return ;
	tputs(res, 0, &ft_putchar_int);
	if (ctl->posy != ctl->len_cmd / ctl->termsize->ws_col)
	{
		ft_savecursor();
		ft_eraselines();
		ft_restorecursor();
	}
}
