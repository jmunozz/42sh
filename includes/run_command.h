#ifndef RUN_COMMAND
# define RUN_COMMAND

# include "minishell.h"

/*
**fork.c
*/
void			ft_fewef(char *command, char **argv, char **env);
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
t_list			*ft_lexer(char *cmd, t_config *config);
char			*ft_envvarinsert(char *cmd, size_t *i, t_config *config);
t_list			*ft_op_handle(char *cmd, size_t *i, t_list **next, t_config *config);
int				ft_dodge_quote(char *cmd, size_t i);
t_list			**ft_quote_handle(t_list **next, t_config *config);
size_t			ft_match_op(char *cmd, size_t *i);

#endif
