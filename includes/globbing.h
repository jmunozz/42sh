#ifndef GLOBBING_H
# define GLOBBING_H

# include "minishell.h"

/*
** globbing.c
*/
void	ft_glob(DIR *dir, char *path, char *glob);
/*
** match.c
*/
int		ft_match(char *glob, char *comp);

#endif
