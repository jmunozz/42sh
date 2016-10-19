/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:22:38 by rbaran            #+#    #+#             */
/*   Updated: 2016/06/01 17:56:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static void	ft_editrmcmd(char **cmdline, t_ctlinput *ctl)
{
	if (!*cmdline || ctl->posx == ctl->initposx)
		return ;
	ft_moveleft(ctl);
	ft_memmove((*cmdline) + (ctl->posx - ctl->initposx),
				((*cmdline) + (ctl->posx - ctl->initposx + 1)),
				ft_strlen((*cmdline) + (ctl->posx - ctl->initposx + 1)) + 1);
	ft_erase(ctl);
	ctl->len_cmd--;
	ft_savecursor();
	ft_putstr((*cmdline) + (ctl->posx - ctl->initposx));
	ft_restorecursor();
}

static void	ft_editcmd(char *buf, char **cmdline, t_ctlinput *ctl)
{
	char	*kill;

	ctl->len_cmd++;
	if (!*cmdline)
		*cmdline = ft_strdup(buf);
	else
	{
		kill = *cmdline;
		if ((*cmdline = ft_strnew(ctl->len_cmd + 1)))
		{
			ft_strncpy(*cmdline, kill, ctl->posx - ctl->initposx);
			ft_strcat(*cmdline, buf);
			ft_strcat(*cmdline, kill + ctl->posx - ctl->initposx);
			free(kill);
		}
	}
	ft_savecursor();
	ft_putstr((*cmdline) + (ctl->posx - ctl->initposx));
	ft_restorecursor();
	ft_moveright(ctl);
}

int			ft_moveaction(unsigned int buf)
{
	static unsigned int	tabvalue[2] = {LEF, RIG};
	int					i;

	i = 0;
	while (i < 2)
	{
		if (tabvalue[i] == buf)
			return (i);
		i++;
	}
	return (-1);
}

void		ft_scanchr(char *buf, char **cmdline, t_conf *config,
					t_ctlinput *ctl)
{
	static void	(*move[2])(t_ctlinput *ctl) = {&ft_moveleft,
			&ft_moveright};
	int			i;

	if (((unsigned int*)buf)[0] == TAB)
		return ;
	if (ft_isprint(((unsigned int*)buf)[0]))
		ft_editcmd(buf, cmdline, ctl);
	else if (config->term == 1 && ((unsigned int*)buf)[0] == SUP)
		ft_editrmcmd(cmdline, ctl);
	else if (config->term == 1 &&
			(i = ft_moveaction(((unsigned int*)buf)[0])) != -1)
		(move[i])(ctl);
	else if (config->term == 1 &&
		(((unsigned int*)buf)[0] == UPP || ((unsigned int*)buf)[0] == DO))
		ft_searchhistory(ctl, config, ((unsigned int*)buf)[0], cmdline);
}
