#ifndef RUN_COMMAND
# define RUN_COMMAND

# include "minishell.h"
# define PIPE 2
# define HEREDOC 3
# define PROS 100
# define SENT 101
# define JOB 102

/*
**exec.c
*/
void			ft_execve(char **argv, char **env, t_config *config);
void			ft_launch_process(t_list *begin, t_config *config);
void			ft_kill_father(t_config *config);
/*
**files.c
*/
int				ft_access_dir(char const *path);
int				ft_access_exec(char *path, char **argv, t_config *config);
/*
**lexer.c
*/
void			ft_list_free_av(void *data, size_t data_size);
t_list			*ft_freelist(t_list *begin);
t_list			*ft_lexer(char *cmd);
char			*ft_envvarinsert(char *cmd, size_t *i, t_config *config);
t_list			*ft_op_handle(char *cmd, size_t *i, t_list **next);
int				ft_dodge_quote(char *cmd, size_t i);
t_list			**ft_quote_handle(t_list **next, t_config *config);
char			*ft_match_op(char *cmd, size_t *i);
/*
**parser.c
*/
int				ft_build_pipe(t_list *begin, t_config *config, int **r_pipe);
void			ft_parse(t_list *begin, t_config *config);
 t_list			*ft_run_sentence(t_list *begin, t_config *config, int *r_pipe);
/*
**wait.c
*/
int				ft_wait(t_list **process);
void			ft_wait_sentence(t_list *job, char *sentence, t_config *config);
/*
**heredoc.c
*/
void			ft_heredocmode(int mode);
void			ft_heredoc(char *cmd, size_t *i, t_list **next);

#endif
