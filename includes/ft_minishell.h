/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:55:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/06/01 16:05:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <libft.h>
# include "minishell_typedefs.h"
# include "minishell_keymap.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <termcap.h>
# include <termios.h>

/*
** Flag error_exit
*/
# define EXIT 0
# define KEEP 1

/*
** File type
*/
# define FILES 0
# define DIRECTORY 1

/*
** Error Type
*/
# define CMD_NOTFOUND		"Command not found"
# define FILE_NOTFOUND		"No such file or directory"
# define FILE_NOTDIR		"Not a directory"
# define FILE_PERMDENIED	"Permission denied"
# define FEW_ARG			"Too few arguments"
# define MANY_ARG			"Too many arguments"
# define BACKUP_TERM		"Sry dude, can not create termios backup"
# define SET_TERM			"Sry dude, can not set termios attr"
# define GET_TERM_SIZE		"Sry dude, can't get terminal size for some reasons"
# define TERM_NOTFOUND		"TERM environment variable is not set"
# define SIG_INT			"Could not set the SIGINT signal"
# define SIG_STOP			"Could not set the SIGSTOP signal"

/*
** Binary mask (param builtin env)
*/
# define PARAM_I 0000002

/*
** Error function
*/
void	ft_error(char *name, char *error, int flag_exit);

/*
** Manage lst
*/
t_bin	*ft_findlast(t_bin *bin);

/*
** Creating config (environment + bin)
*/
t_conf	*ft_fillconf(char **env);

/*
** Manage environment
*/
char	**ft_parseenv(char **env, char *variable);
int		ft_findenv(char **env, char *variable);
char	**ft_fillenv(char **env, size_t size);
void	ft_printenv(char **env);

/*
** Free
*/
void	ft_free_split(char **split);
void	ft_free_bin(t_bin **bin);

/*
** Hash function
*/
void	ft_hashtable(t_conf *config);
t_bin	*ft_hashsearch(t_conf *config, char *cmd);

/*
** Shell prompt
*/
void	ft_printprompt(void);

/*
** Builtins
*/
void	ft_cd(t_conf *config, char **cmd_split);
void	ft_exit(t_conf *config, char **cmd_split);
void	ft_unsetenv(t_conf *config, char **cmd_split);
void	ft_setenv(t_conf *config, char **cmd_split);
void	ft_env(t_conf *config, char **cmd_split);

/*
** Access dir/file
*/
int		ft_access(char *path, int type);

/*
** Exec commands
*/
void	ft_minishell(t_conf *config);
t_bin	*ft_findcmd(char *cmd, t_bin *cmds);
void	ft_execcmd(t_bin *cmd, char **cmdline_split, t_conf *config);
int		ft_findbuiltin(char *cmd);

/*
** Utils
*/
size_t	ft_splitsize(char **split);

/*
** Scan input
*/
char	*ft_scaninput(t_conf *config);
void	ft_scanchr(char *buf, char **cmdline, t_conf *config, t_ctlinput *ctl);
void	ft_moveleft(t_ctlinput *ctl);
void	ft_moveright(t_ctlinput *ctl);
int		ft_putchar_int(int c);
void	ft_savecursor(void);
void	ft_restorecursor(void);
void	ft_erase(t_ctlinput *ctl);

/*
** History
*/
void	ft_searchhistory(t_ctlinput *ctl, t_conf *conf, unsigned int buf, char **cmdline);

#endif
