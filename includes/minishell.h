/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:23:28 by tboos             #+#    #+#             */
/*   Updated: 2016/05/11 14:26:57 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# define HISTORY_SIZE 256
# define FT_PUTSTRFD ft_putstr_str_str_fd
# define CLF 0x0A //\n
# define SUP 0x7E335B1B //sup
# define CHT 0x09 //\t
# define DEL 0x7F //DEL
# define LEF 0x445B1B //left
# define RIG 0x435B1B //right
# define UPP 0x415B1B //up
# define DOW 0x425B1B //down
# define CLEF 0x44353B315B1B //CTRL left
# define CRIG 0x43353B315B1B //CTRL up
# define CUPP 0x41353B315B1B //CTRL right
# define CDOW 0x42353B315B1B //CTRL down
# define END 0x464F1B //end
# define HOM 0x484F1B //home
# define NUL 0x00 //\0
# define QUOTE_ERR "please end your quote before running command"
# define PAR_ERR "missing '(' ')' '[' ']' '{' '}' character"
# define BACK_ERR "missing character after backslash"

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
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
	size_t		prompt_len;
	t_list		*bin;
	t_list		*h_bin[34];
	t_termios	termios;
	t_termios	termios_backup;
	int			term_state;
	char		*history[HISTORY_SIZE + 1];
	int			hindex;
}				t_config;
typedef struct	s_stream
{
	char		*term;
	char		*tput;
	int			fd;
	int			ret;
	int			shindex;
	int			state;
	char		buf[9];
	char		*command;
	char		*kill;
	size_t		pos;
	size_t		col;
	t_config	*config;
}				t_stream;
/*
**streamscan.c
*/
char			*ft_streamscan(t_config *config, int fd);
int				ft_underline_mess(char *mess, t_stream *stream);
int				ft_quotecheck(t_stream *stream);
/*
**termcaps.c
*/
int				ft_putcharint(int	i);
void			ft_tputs(t_stream *stream);
void			ft_mvleft(t_stream *stream);
void			ft_mvright(t_stream *stream);
/*
**arrowlr.c && arrowud.c
*/
void			ft_ctrlleft(t_stream *stream);
void			ft_ctrlright(t_stream *stream);
void			ft_left(t_stream *stream);
void			ft_right(t_stream *stream);
void			ft_goend(t_stream *stream);
void			ft_gohome(t_stream *stream);
void			ft_ctrlup(t_stream *stream);
void			ft_ctrldown(t_stream *stream);
/*
**deletion.c
*/
void			ft_clean_field(t_stream *stream);
void			ft_erase(t_stream *stream);
void			ft_sup(t_stream *stream);
void			ft_del(t_stream *stream);
/*
**chrparse.c
*/
void			ft_flushend(t_stream *stream);
void			ft_flush(t_stream *stream);
int				ft_chrparse(t_stream *stream);
/*
**autocomp.c
*/
void			ft_autocomp(t_stream *stream);
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
void			ft_up(t_stream *stream);
void			ft_down(t_stream *stream);
void			ft_decr_history(int *hindex);
void			ft_incr_history(int *hindex);
void			ft_push_history(t_stream *stream, t_config *config);
/*
**error.c
*/
int				ft_initerror(void);
int				ft_malloc_error(char const *path);
void			ft_lexer_error(char *command);
void			ft_fork_error(void);
void			ft_term_error(t_config *config);
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
