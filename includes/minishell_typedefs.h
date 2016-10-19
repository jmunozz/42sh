/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 12:51:24 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/30 16:30:11 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEFS_H
# define MINISHELL_TYPEDEFS_H

typedef struct dirent	t_dirent;

typedef struct	s_bin
{
	char			*name;
	char			*path;
	struct s_bin	*next;
}				t_bin;

typedef struct	s_conf
{
	t_bin	*bin;
	t_bin	*hashtable[63];
	t_list	*history;
	t_list	*begin_history;
	char	**env;
	char	term;
}				t_conf;

typedef struct	s_ctlinput
{
	struct winsize	*termsize;
	int				initposx;
	int				posx;
	int				posy;
	int				len_cmd;
}				t_ctlinput;

#endif
