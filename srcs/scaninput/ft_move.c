/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:29:03 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_moveup(t_ctlinput *ctl)
{
	char	*res;
	int		i;

	res = tgetstr("up", NULL);
	if (!res)
		return ;
	tputs(res, 0, &ft_putchar_int);
	res = tgetstr("nd", NULL);
	ctl->posy--;
	i = -1;
	while (++i <= ctl->termsize->ws_col)
		tputs(res, 0, &ft_putchar_int);
}

static void	ft_movedown(t_ctlinput *ctl)
{
	char	*res;
	int		i;

	res = tgetstr("do", NULL);
	if (!res)
		return ;
	tputs(res, 0, &ft_putchar_int);
	res = tgetstr("le", NULL);
	ctl->posy++;
	i = ctl->termsize->ws_col;
	while (--i >= 0)
		tputs(res, 0, &ft_putchar_int);
}

void		ft_moveright(t_ctlinput *ctl)
{
	char	*res;

	res = NULL;
	if (ctl->posx >= ctl->len_cmd)
		return ;
	ctl->posx++;
	if (ctl->posx / ctl->termsize->ws_col == ctl->posy)
		res = tgetstr("nd", NULL);
	else
		ft_movedown(ctl);
	if (res)
		tputs(res, 0, &ft_putchar_int);
}

void		ft_moveleft(t_ctlinput *ctl)
{
	char	*res;

	res = NULL;
	if (ctl->posx == ctl->initposx)
		return ;
	ctl->posx--;
	if (ctl->posx / ctl->termsize->ws_col == ctl->posy)
		res = tgetstr("le", NULL);
	else
		ft_moveup(ctl);
	if (res)
		tputs(res, 0, &ft_putchar_int);
}
