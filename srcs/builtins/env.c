/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:14:44 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/09 19:34:37 by rbaran           ###   ########.fr       */
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
	char	*unset[3];
	int		i;

	unset[2] = NULL;
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
			unset[1] = argv[i];
			ft_unsetenv((char**)unset, config);
		}
		else
			break ;
	}
	return (i);
}

static void	ft_createenv(char **argv, t_config *config, int *index)
{
	char	*equal;

	while (argv[*index] && (equal = ft_strchr(argv[*index], '=')))
	{
		*equal = '\0';
		ft_setenv(argv[*index], equal + 1, config);
		ft_putstrtab(config->env, '\n');
		(*index)++;
	}
}

int			ft_env(char **argv, t_config *config)
{
	int		param;
	int		i;

	if (!argv[1])
	{
		ft_putstrtab((config->env), '\n');
		ft_putchar('\n');
		return (1);
	}
	param = 0;
	i = ft_parseparams(argv, &param, config);
	if (param & ENV_H)
	{
		ft_printhelp();
		return (1);
	}
	if (param & ENV_I)
	{
		ft_strtabfree(config->env);
		config->env = NULL;
	}
	ft_createenv(argv, config, &i);
	return (0);
}
