/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:02 by tboos             #+#    #+#             */
/*   Updated: 2016/03/31 13:15:38 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shell_exit(t_config *config, char **argv)
{
	if (argv)
		ft_strtabfree(argv);
	ft_free_config(config);
	exit(ft_status(0));
}

void	ft_freebin(void *data, size_t data_size)
{
	if (data_size)
	{
		free(((t_bin *)data)->path_name);
		free(data);
	}
}

void	ft_free_config(t_config *config)
{
	if (config)
	{
		ft_free_all_jobs(&(config->jobs));
		ft_freegiveone((void **)&(config->pwd));
		if (config->env)
			ft_strtabfree(config->env);
		if (config->bin)
			ft_lstdel(&(config->bin), &ft_freebin);
		if (config->hloc)
			ft_purge_history(config);
		if (config->hloc)
			free(config->hloc);
		get_next_line(-1, NULL);
	}
}

void			ft_list_free_av(void *data, size_t data_size)
{
	if (!data_size && data)
		ft_strtabfree((char **)data);
	else if (data_size == OP || data_size == PIPE || data_size == HEREDOC)
		free(data);
	else if (data_size == SSHELL)
		ft_freelist((t_list *)data);
}

t_list			*ft_freelist(t_list *begin)
{
	ft_lstdel(&begin, ft_list_free_av);
	return NULL;
}
