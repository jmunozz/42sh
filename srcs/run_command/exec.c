/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2016/11/03 17:54:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_path_handle(t_list *begin, t_config *config)
{
	char	**argv;
	char	*bin;

	argv = (char**)begin->data;
	if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "echo")
		||!ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "printenv"))
		return (1);
	if ((bin = ft_return_binpath(config, argv[0]))
		&& ft_freegiveone((void**)&(argv[0]))
		&& !(argv[0] = ft_strdup(bin)))
		ft_error(SHNAME, "exec", "malloc error", CR_ERROR);
	begin->data = (void*)argv;
	return (ft_access_exec(argv[0], argv, config));
}

void		ft_execve(char **argv, char **env)
{
	if (-1 == execve(argv[0], argv, env))
		ft_error(SHNAME, "exec", "execve error", CR_ERROR);
}

void		ft_launch_process(t_list *begin, t_config *config)
{
	if (ft_builtin((char **)(begin->data), config))
		return ;
	ft_execve((char **)(begin->data), config->env);
}

void		ft_kill_father(t_config *config)
{
	ft_free_config(config);
	if (-1 == kill(getppid(), SIGKILL))
		ft_error(SHNAME, "SORRY", JEDI_ERR, CR_ERROR);
	exit(0);
}
