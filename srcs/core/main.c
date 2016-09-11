/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/09/11 21:37:45 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_manage_files(int ac, char **av, t_config *config)
{
	char		*cmd;
	int			fd;
	int			i;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0 || -1 == read(fd, cmd, 0))
			FT_PUTSTRFD("minishell: can't open input file: ",
					av[i], "\n", 2);
		else
		{
			while ((get_next_line(fd, &cmd)))
			{
				ft_run_command(config, cmd);
				free(cmd);
			}
			close(fd);
		}
	}
}

static void	ft_tricase(int ac, char **av, t_config *config)
{
	if (ac == 1)
		ft_minishell(config);
	ft_manage_files(ac, av, config);
	ft_shell_exit(config, NULL);
}

static void	ft_termcaps_init(t_config *config)
{
	char		*i;

	i = ft_strtabfindstart(config->env, "TERM=");
	if (i && tgetent(NULL, i + 5))
		config->term_state = 1;
	else
		ft_term_error(config);
}

static int	ft_history_loc_init(t_config *config, char *av)
{
	char		*c;

	if (!(c = ft_strtabfindstart(config->env, "PWD"))
		|| !(c = ft_strslashjoin(c + 4, av)))
		return (ft_initerror(config));
	if (!(config->hloc = ft_strrchr(c, '/')))
		return (ft_initerror(config));
	config->hloc[0] = '\0';
	if (!(config->hloc = ft_strslashjoin(c, "history.bck"))
		&& ft_freegiveone((void**)&c))
		return (ft_initerror(config));
	ft_freegiveone((void**)&c);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_config	config;
	int			i;

	ft_bzero(&config, sizeof(t_config));
	if (!env || !env[0] || !(config.env = ft_strtabdup(env))
		|| !ft_pathtohash(&config))
		if (!ft_default_env(&config) || !ft_pathtohash(&config))
			return (ft_initerror(&config));
	if ((i = ft_strtabifindstart(env, "SHLVL")) != -1)
		ft_setenv("SHLVL", ft_itoa(ft_atoi(env[i] + 6) + 1), &config);
	if (ft_history_loc_init(&config, av[0]))
		return (1);
	ft_termcaps_init(&config);
	ft_tricase(ac, av, &config);
	return (0);
}
