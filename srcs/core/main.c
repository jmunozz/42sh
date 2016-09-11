/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 14:43:21 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_signal(void)
{
//	if (SIG_ERR == signal(SIGINT, SIG_IGN))
//		return (ft_initerror());
//	if (SIG_ERR == signal(SIGTSTP, SIG_IGN))
//		return (ft_initerror());
	return (0);
}

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
	if (ac > 1)
		ft_manage_files(ac, av, config);
	else if (!ft_signal())
		ft_minishell(config);
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

int			main(int ac, char **av, char **env)
{
	t_config	config;

	ft_bzero(&config, sizeof(t_config));
	if (!env || !env[0] || !(config.env = ft_strtabdup(env))
		|| !ft_pathtohash(&config))
		if (!ft_default_env(&config) || !ft_pathtohash(&config))
			return (ft_initerror(&config));
	ft_termcaps_init(&config);
	ft_tricase(ac, av, &config);
	return (0);
}
