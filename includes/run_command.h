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

#endif
