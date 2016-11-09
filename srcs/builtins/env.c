/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:14:44 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/09 19:48:04 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_printhelp(void)
{
	ft_putstr("HOY\n");
	return ;
}

static void	ft_parseparams(char **argv, int *param, t_config *config)
{
	char	*unset[3];
	char	**next;

	unset[2] = NULL;
	next = argv;
	while (*argv && (*argv)[0] == '-')
	{
		if ((*argv)[1] == 'h' || !ft_strcmp(*argv, ENV_HELP))
			*param |= ENV_H;
		else if ((*argv)[1] == 'i' || !ft_strcmp(*argv, ENV_IGNORE))
			*param |= ENV_I;
		else if (((*argv)[1] == 'u' || !ft_strcmp(*argv, ENV_UNSET)))
		{
			unset[1] = *(argv + 1);
			ft_unsetenv((char**)unset, config);
			ft_freegiveone((void**)*argv);
			next = argv + 1;
			*argv = *next;
		}
		else
			break ;
		next = argv + 1;
		ft_freegiveone((void**)*argv);
		*argv = *next;
	}
}

static void	ft_createenv(char **argv, t_config *config)
{
	char	*equal;
	char	**next;

	while (*argv && (equal = ft_strchr(*argv, '=')))
	{
		next = argv + 1;
		*equal = '\0';
		ft_setenv(*argv, equal + 1, config);
		ft_putstrtab(config->env, '\n');
		ft_freegiveone((void**)*argv);
		*argv = *next;
	}
}

int			ft_env(char **argv, t_config *config)
{
	int		param;

	if (!argv[1])
	{
		ft_putstrtab((config->env), '\n');
		ft_putchar('\n');
		return (1);
	}
	param = 0;
	ft_parseparams(argv, &param, config);
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
	ft_createenv(argv, config);
	return (0);
}
