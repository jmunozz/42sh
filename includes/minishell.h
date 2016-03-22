/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:23:28 by tboos             #+#    #+#             */
/*   Updated: 2016/03/18 18:18:24 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include "libft.h"
typedef struct	dirent	t_dirent;
typedef struct	s_exe
{
	char		*name;
	char		*path_name;
}				t_exe;
typedef struct	s_config
{
	char		**env;
	t_list		*exe;
	int			h_exe[29];
}				t_config;

void	ft_free_config(t_config *config);
void	ft_minishell(t_config *config);
int		ft_prompt(t_config *config);
#endif
