/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/11/03 17:27:06 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_manage_files(int ac, char **av, t_config *config)
{
	int			fd;
	int			i;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			ft_error(SHNAME, "can't open input file", av[i], CR_ERROR | SERROR);
		else
		{
			ft_shname_or_file(av[i]);
			ft_script_line(-1);
			while ((get_next_line(fd, &config->command)) > 0
				&& ft_script_line(1))
				ft_run_command(config);
			get_next_line(-1, NULL);
			close(fd);
			ft_shname_or_file(SHNAME);
		}
	}
}

static void	ft_termcaps_init(t_config *config)
{
	char		*i;

	i = ft_strtabfindstart(config->env, "TERM=");
	if (i && tgetent(NULL, i + 5))
		config->term_state = 1;
	else
	{
		ft_error(SHNAME, ANSI_USE, BEAWARE_ERR, CR_ERROR);
		config->term_state = 0;
	}
}

static void	ft_tricase(int ac, char **av, t_config *config)
{
	if (ac == 1)
	{
		if (isatty(0))
		{
			ft_termcaps_init(config);
			ft_minishell(config);
		}
		else
		{
			while (get_next_line(0, &config->command) > 0 && ft_script_line(1))
				ft_run_command(config);
			get_next_line(-1, NULL);
		}
	}
	else
		ft_manage_files(ac, av, config);
	ft_shell_exit(config);
}


static int	ft_history_loc_init(t_config *config, char *av)
{
	char		*c;

	if (!config->pwd || !(c = ft_strslashjoin(config->pwd, av)))
		return (ft_initerror(config));
	if (!(config->hloc = ft_strrchr(c, '/')) && ft_freegiveone((void**)&c))
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
	ft_update_pwd(&config);
	if ((i = ft_strtabifindstart(env, "SHLVL")) != -1)
		ft_setenv("SHLVL", ft_st_itoa(ft_atoi(env[i] + 6) + 1), &config);
	if (ft_history_loc_init(&config, av[0]))
		return (1);
	ft_tricase(ac, av, &config);
	return (0);
}
