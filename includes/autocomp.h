#include "minishell.h"

/*
** getenv.c
*/
int		ft_getenvline(char *str, char **e);
char	**ft_getenvtab(char *str, char **e);
/*
** autocomp.c
*/
int		ft_is_separator(char c);
int		get_mode(int len, char *str, t_stream *stream);
void	ft_autocomp(t_stream *stream);
/*
** buildlist.c
*/
void	build_list(t_list **list, char *str, int mode, t_stream *stream);

