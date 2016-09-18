#ifndef INPUT_SCAN_H
# define INPUT_SCAN_H

# define TUP "\x1b[A"
# define TDO "\x1b[B"
# define TLE "\x1b[D"
# define TND "\x1b[C"
# define TDL "\x1b[K"
# define TCD "\x1b[J"

typedef struct	s_stream
{
	char		*tput;
	int			fd;
	int			ret;
	int			shindex;
	int			state;
	char		buf[9];
	char		*command;
	char		*kill;
	char		*search;
	size_t		pos;
	size_t		col;
	t_config	*config;
}				t_stream;
/*
**streamscan.c
*/
char			*ft_streamscan(t_config *config, t_stream *stream, int fd);
/*
**underlinemess.c
*/
int				ft_underline_mess(char *mess, t_stream *stream);
/*
**quotecheck.c
*/
char			*ft_matchchr(char **str);
int				ft_quotecheck(t_stream *stream);
/*
**termcaps.c
*/
int				ft_putcharint(int	i);
void			ft_tputs(t_stream *stream);
void			ft_mvleft(t_stream *stream);
void			ft_mvright(t_stream *stream);
void			ft_gomatch(t_stream *stream, unsigned int go,
							void (*mv)(t_stream *));
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
void			ft_erase(t_stream *stream);
void			ft_clean_field(t_stream *stream);
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
**prompt.c
*/
void			ft_prompt(t_config *config);
/*
**history.c
*/
void			ft_up(t_stream *stream);
void			ft_down(t_stream *stream);
void			ft_decr_history(int *hindex);
void			ft_incr_history(int *hindex);
void			ft_push_history(t_stream *stream, t_config *config);
void			ft_load_history(t_config *config);
void			ft_purge_history(t_config *config);
void			ft_searchengine(t_stream *stream);
void			ft_sappend(t_stream *stream);
void			ft_sdel(t_stream *stream);
void			ft_sprompt(t_stream *stream);
void			ft_searchinhistory(t_stream *stream);
void			ft_flushsearch(t_stream *stream);
/*
**winsize.c
*/
t_stream		*ft_save_stream(t_stream *stream);
void			ft_winsize(void);
void			ft_prompt_reset(t_stream *stream);

#endif
