/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:35 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 18:29:40 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_default_env(t_config *config)
{
	char	*d[3];
	char	buf[256];

	ft_free_config(config);
	d[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (!(d[1] = getcwd(buf, 256)) || !(d[1] = ft_strjoin("PWD=", d[1])))
		return false;
	d[2] = NULL;
	if (!(config->env = ft_strtabdup(d)) && ft_freegiveone((void **)&(d[1])))
		return false;
	ft_freegiveone((void **)&(d[1]));
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
	char	*p;

	i = 0;
	while (argv[++i])
	{
		if ((t = ft_strchr(argv[i], '=')))
		{
			*t = '\0';
			p = argv[i] - 1;
			while (*(++p))
				*p = ft_toupper(*p);
			while (*(++p))
				*p = ft_tolower(*p);
		}
		ft_setenv(argv[i], t + 1, config);
	}
}

void	ft_unsetenv(char **argv, t_config *config)
{
	int		i;

	i = 0;
	while (argv[++i])
		ft_strncmptabdel(config->env, argv[i]);
}
