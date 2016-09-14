/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:35 by tboos             #+#    #+#             */
/*   Updated: 2016/09/11 21:35:14 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_default_env(t_config *config)
{
	t_passwd	*passwd;

	ft_free_config(config);
	if (!(config->env = (char **)ft_memalloc(sizeof(char*))))
		return false;
	ft_setenv("PATH", DPATH, config);
	if ((passwd = getpwuid(getuid())))
	{
		ft_setenv("USER", passwd->pw_name, config);
		ft_setenv("HOME", passwd->pw_dir, config);
	}
	ft_setenv("SHLVL", "1", config);
	return true;
}

void	ft_setenv(char *name, char *value, t_config *config)
{
	int		i;
	char	**f;
	char	*memo;

	f = config->env;
	if ((i = ft_strtabifindstart(f, name)) >= 0
		&& (memo = f[i])
		&& !(f[i] = ft_strchrjoin(name, '=', value))
		&& (f[i] = memo))
		FT_PUTSTRFD("minishell: error while setenv for: ", name, "\n", 2);
	else if (i >= 0 && !ft_strcmp(name, "PWD"))
	{
		ft_setenv("OLDPWD", memo + 4, config);
		free(memo);
	}
	else if (i < 0 && !(memo = ft_strchrjoin(name, '=', value)))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ",
				name, "\n", 2);
	else if (i < 0 && !(config->env = ft_strtabadd(config->env, memo))
		&& ft_freegiveone((void **)&memo) && (config->env = f))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ",
				name, "\n", 2);
	else if (f && config->env && f != config->env)
		free(f);
	if (!ft_strcmp("PATH", name))
		ft_pathtohash(config);
}

void	ft_env(char **argv, t_config *config)
{
	char	*envbin;

	if (!argv[1])
	{
		ft_putstrtab((char const **)(config->env), '\n');
		ft_putchar('\n');
	}
	else if (!(envbin = ft_return_binpath(config, "env")))
		ft_putendl_fd("minishell: unnable to find advanced env", 2);
	else
		ft_access_exec(envbin, argv, config);
}

void	ft_readysetenv(char **argv, t_config *config)
{
	int		i;
	char	*t;

	i = 0;
	while (argv[++i])
	{
		if ((t = ft_strchr(argv[i], '=')))
			*t = '\0';
		ft_setenv(argv[i], t + 1, config);
	}
}

void	ft_unsetenv(char **argv, t_config *config)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		ft_strncmptabdel(config->env, argv[i]);
		if (!ft_strncmp("PATH", argv[i], 4) && strlen(argv[i]) == 4)
			ft_pathtohash(config);
	}
}
