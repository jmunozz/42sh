/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:08:52 by rbaran            #+#    #+#             */
/*   Updated: 2016/06/01 17:56:12 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

void		ft_searchhistory(t_ctlinput *ctl, t_conf *config,
				unsigned int buf, char **cmdline)
{
	t_list	*lstbuf;

	if (!(config->begin_history))
		return ;
	lstbuf = (buf == UPP) ? config->history :
			ft_lstfindprev(&(config->begin_history), &(config->history));
	if (!lstbuf)
		return ;
	config->history = lstbuf->next;
	while (ctl->posx > ctl->initposx)
		ft_moveleft(ctl);
	ft_erase(ctl);
	if (*cmdline)
		free(*cmdline);
	if ((*cmdline = ft_strdup((char*)(lstbuf->content))))
	{
		ft_putstr(*cmdline);
		ctl->len_cmd = ft_strlen(*cmdline) + ctl->initposx;
		ctl->posx = ctl->len_cmd;
	}
}
