/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printprompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 15:19:20 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/26 16:35:53 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_printprompt(void)
{
	char	buf[256];
	char	*pwd;

	pwd = getcwd(buf, 256);
	ft_putstr("\033[32m");
	if (*(ft_strrchr(pwd, '/') + 1))
		ft_putstr(ft_strrchr(pwd, '/') + 1);
	else
		ft_putstr(pwd);
	ft_putstr("\033[00m > ");
}
