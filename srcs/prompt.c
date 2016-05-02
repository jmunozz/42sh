/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 16:37:59 by tboos             #+#    #+#             */
/*   Updated: 2016/03/23 20:21:26 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_goprompt(t_config *config, char *loc)
{
	ft_putstr("\x1b[34m-> \x1b[1;32m");
	ft_putstr(loc);
	ft_putstr(" : \x1b[0m");
	config->prompt_len = ft_strlen(loc) + 6;
}

int		ft_prompt(t_config *config)
{
	char	*pwd;
	char	*subrep;
	char	buf[256];

	if (!(pwd = ft_strtabfindstart(config->env, "PWD")))
	{
		if (!getcwd(buf, 256) || !(pwd = ft_strjoin("PWD=", buf)))
		{
			ft_putstr_fd("minishell: prompt error: path to long\n", 2);
			ft_goprompt(config, "prompting");
			return (1);
		}
		ft_setenv("PWD", pwd + 4, config);
	}
	if ((subrep = ft_strrchr(pwd, '/')) && *(subrep + 1))
		ft_goprompt(config, subrep + 1);
	else
		ft_goprompt(config, pwd + 4);
	return (1);
}
