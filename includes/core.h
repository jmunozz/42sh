#ifndef CORE_H
# define CORE_H

# define SHELL_NAME "21sh"
# define HISTORY_SIZE 100
# define FT_PUTSTRFD ft_putstr_str_str_fd
# define QUOTE_ERR "please end your quote before running command"
# define PAR_ERR "missing '(' ')' '[' ']' '{' '}' or \"`\" character"
# define BACK_ERR "missing character after backslash"

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
typedef struct passwd	t_passwd;
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
	char		*hloc;
	int			hindex;
}				t_config;
/*
**builtin.c && environ.c
*/
int				ft_default_env(t_config *config);
int				ft_builtin(char **argv, t_config *config);
void			ft_cd(char **argv, t_config *config);
void			ft_env(char **argv, t_config *config);
void			ft_setenv(char *name, char *value, t_config *config);
void			ft_readysetenv(char **argv, t_config *config);
void			ft_unsetenv(char **argv, t_config *config);
/*
**error.c
*/
int				ft_initerror(t_config *config);
int				ft_malloc_error(char const *path);
void			ft_lexer_error(char *command);
void			ft_fork_error(void);
void			ft_term_error(t_config *config);
/*
**hash.c && cmp.c
*/
int				ft_pathtohash(t_config *config);
char			*ft_return_binpath(t_config *config, char *name);
int				ft_ascii_cmp(t_bin *s1, t_bin *s2);
/*
**free.c
*/
void			ft_shell_exit(t_config *config, char **argv);
void			ft_freebin(void *data, size_t data_size);
void			ft_free_config(t_config *config);
/*
**main.c && minishell.c
*/
void			ft_run_command(t_config *config, char *cmd);
void			ft_minishell(t_config *config);
/*
**signal.c
*/
int				ft_signal(void);
void			ft_signal_handle(int i);
void			ft_sigwinch(void);

#endif
