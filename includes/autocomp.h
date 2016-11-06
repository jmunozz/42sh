#ifndef AUTOCOMP_H
# define AUTOCOMP_H

# include "minishell.h"

# define COMP_PAD			stream->comp->pad
# define COMP_COL			stream->col
# define COMP_SIZE_LIST		stream->comp->size_list
# define COMP_BEGIN_LIST	stream->comp->begin_list
# define COMP_IN_COL		stream->comp->in_col

/*
** getenv.c
*/
int		ft_getenvline(char *str, char **e);
char	**ft_getenvtab(char *str, char **e);
/*
** autocomp.c
*/
char	*list_to_char(t_stream *stream, t_list *list);
int		ft_is_separator(char c);
int		get_mode(int len, char *str, t_stream *stream);
void	ft_autocomp(t_stream *stream);
/*
** buildlist.c
*/
void	build_list(char *str, int mode, t_stream *stream);
/*
** support.c
*/
void	get_pad(t_stream *stream, char *str);
void	get_size_list(t_stream *stream);
void	init_comp(t_stream *stream);
/*
** print.c
*/
void	ft_print_autocomp(t_stream *stream);
void	ft_print_col(t_stream *stream);
void	get_col_elem(t_stream *stream);

#endif
