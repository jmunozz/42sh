/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:23:28 by tboos             #+#    #+#             */
/*   Updated: 2016/03/29 20:28:49 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# define FT_PUTSTRFD ft_putstr_str_str_fd
# define NUL 0x00000000 //\0
# define CBS 0x08000000 //backspace
# define CHT 0x09000000 //\t
# define CLF 0x0A000000 //\n
# define SPA 0x20000000 // 
# define DEL 0x7F000000 //Suppr?

typedef struct dirent	t_dirent;
typedef struct	s_bin
{
	char		*name;
	char		*path_name;
}				t_bin;
typedef struct	s_arguments
{
	char		**argv;
	char		**memo;
}				t_arguments;
typedef struct	s_config
{
	char		**env;
	char		*history[256];
	size_t		prompt_len;
	t_list		*bin;
	t_list		*h_bin[34];
}				t_config;
typedef struct	s_stream
{
	int			fd;
	int			ret;
	int			state;
	char		buf[5];
	char		*command;
	char		*tail;
	char		*kill;
	size_t		pos;
	t_config	*config;
}				t_stream;
struct termios	termios_backup;/*
**streamscan.c
*/
int				ft_termios_handle(int mode);
char			*ft_streamscan(t_config *config, int fd);

/*
**chrparse.c
*/
int				ft_autocomp(t_stream *stream);
int				ft_chrparse(t_stream *stream);
/*
**builtin.c && environ.c
*/
int				ft_builtin(char **argv, t_config *config);
void			ft_cd(char **argv, t_config *config);
void			ft_env(char **argv, t_config *config);
void			ft_setenv(char *name, char *value, t_config *config);
void			ft_readysetenv(char **argv, t_config *config);
void			ft_unsetenv(char **argv, t_config *config);
/*
**files.c
*/
int				ft_access_dir(char const *path);
void			ft_access_exec(char *path, char **argv, t_config *config);
/*
**history.c
*/
void			ft_push_history(char *command, t_config *config);
/*
**error.c
*/
int				ft_initerror(void);
int				ft_malloc_error(char const *path);
void			ft_lexer_error(char *command);
void			ft_fork_error(void);
/*
**fork.c
*/
void			ft_fewef(char *command, char **argv, char **env);
void			ft_kill_father(t_config *config);
/*
**hash.c && cmp.c
*/
int				ft_pathtohash(t_config *config);
char			*ft_return_binpath(t_config *config, char *name);
int				ft_ascii_cmp(t_bin *s1, t_bin *s2);
/*
**free.c
*/
void			ft_free_history(char **history);
void			ft_shell_exit(t_config *config, char **argv);
void			ft_freebin(void *data, size_t data_size);
void			ft_free_config(t_config *config);
/*
**main.c && minishell.c && prompt.c
*/
void			ft_run_command(t_config *config, char *cmd);
void			ft_minishell(t_config *config);
int				ft_prompt(t_config *config);

#endif
