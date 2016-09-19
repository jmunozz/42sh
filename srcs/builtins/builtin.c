/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:16:34 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 14:44:22 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[++i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

static void	ft_pwd(char **argv, t_config *config)
{
	if (argv[1])
		ft_error("pwd", NULL, "too many arguments", CR_ERROR);
	else
		ft_putendl(config->pwd);
}

int			ft_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "exit"))
		ft_shell_exit(config, argv);
	else if (!ft_strcmp(argv[0], "exitfather"))
		ft_kill_father(config);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argv, config);
	else if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv);
	else if (!ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "printenv"))
		ft_env(argv, config);
	else if (!ft_strcmp(argv[0], "unsetenv") || !ft_strcmp(argv[0], "unset"))
		ft_unsetenv(argv, config);
	else if (!ft_strcmp(argv[0], "setenv") || !ft_strcmp(argv[0], "set")
		|| !ft_strcmp(argv[0], "export"))
		ft_readysetenv(argv, config);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, config);
	else
		return (0);
	return (1);
}
