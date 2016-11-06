/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:14:44 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/06 11:00:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_printhelp(void)
{
	ft_putstr("HOY\n");
	return ;
}

static int	ft_parseparams(char **argv, int *param, t_config *config)
{
	char	*unset[2];
	int		i;

	unset[1] = NULL;
	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		if (argv[i][1] == 'h' || !ft_strcmp(argv[i], ENV_HELP))
		{
			*param |= ENV_H;
			break ;
		}
		else if (argv[i][1] == 'i' || !ft_strcmp(argv[i], ENV_IGNORE))
			*param |= ENV_I;
		else if ((argv[i][1] == 'u' || !ft_strcmp(argv[i], ENV_UNSET)) && ++i)
		{
			unset[0] = argv[i];
			ft_unsetenv((char**)unset, config);
		}
		else
			break ;
	}
	return (i);
}

static void	ft_createenv(char **argv, t_config *config, int index)
{
	char	*equal;

	while (argv[index] && (equal = ft_strchr(argv[index], '=')))
	{
		*equal = '\0';
		ft_setenv(argv[index], equal + 1, config);
		index++;
	}
}

void		ft_env(char **argv, t_config *config)
{
	int		param;
	int		i;

	if (!argv[1])
	{
		ft_putstrtab((config->env), '\n');
		ft_putchar('\n');
		return ;
	}
	param = 0;
	i = ft_parseparams(argv, &param, config);
	if (param & ENV_H)
	{
		ft_printhelp();
		return ;
	}
	if (param & ENV_I)
		ft_unsetenv(config->env, config);
	ft_createenv(argv, config, i);
}
