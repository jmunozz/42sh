#include "../../includes/autocomp.h"
/*
 ** Mode = 'D' -> positionne le curseur sur le début de la ligne en dessous de la commande.
 ** Mode = 'U' -> remet le curseur à sa position initiale.
 */
void		ft_autocomp_underline(t_stream *stream, char mode)
{
	size_t				i;
	static unsigned int	pos_buf;

	if (mode == 'D')
	{
		pos_buf = stream->pos;
		ft_goend(stream); //on va au bout de la ligne de commande.
		stream->tput = "do"; //on saute une ligne.
		ft_tputs(stream);
		ft_repeat_termcaps(stream->col, "le", stream); //retourne au début de la ligne.
		stream->tput = "cd"; //clear line cursor and all lines below.
		ft_tputs(stream);
	}
	else
	{
		i = (stream->command) ? stream->config->prompt_len +
			ft_strlen(stream->command) : stream->config->prompt_len; // si pas de comande i = prompt
		i = i % stream->col; // retranche ce qui est du à la présence de plusieurs lignes.
		ft_repeat_termcaps(i, "nd", stream); // on se retrouve sur le dernier caractère de la commande
		ft_gomatch(stream, pos_buf, ft_mvleft); //on remonte jusqu'au caractère enregistré.
	}
}
/*
** Remet la ligne de commande à l'état qui précédait l'appel à ft_autocomp_append.
*/
void		ft_autocomp_delete(t_stream *stream)
{
	char	*kill;
	size_t	len;

	ft_gohome(stream);
	stream->tput = "cd";
	ft_tputs(stream);
	len = ft_strlen(COMP_BUF);
	if ((kill = stream->command))
	{
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) - len)))
			return;
		ft_strncpy(stream->command, kill, COMP_POS_COMMAND);
		ft_strcpy(stream->command + COMP_POS_COMMAND, kill + COMP_POS_COMMAND + len);
		ft_putstr(stream->command);
		stream->pos += (ft_strlen(stream->command) % stream->col);
		ft_freegiveone((void**)&kill);
	}
	ft_gomatch(stream, COMP_POS_COMMAND, ft_mvleft);
}
/*
** Version de append qui diffère en ce qu'elle fait appel à un buffer particulier COMP_BUF.
*/
void		ft_autocomp_append(t_stream *stream)
{
	size_t				pos;
	size_t				len;
	char				*kill;

	len = ft_strlen(COMP_BUF);
	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + len))
				&& (stream->state = -2) && ft_freegiveone((void **)&kill))
			return ;
		ft_strncpy(stream->command, kill, pos);
		ft_strcpy(stream->command + pos, COMP_BUF);
		ft_strcpy(stream->command + pos + len, kill + pos);
		ft_freegiveone((void **)&kill);
	}
	else if (!(stream->command = ft_strdup(COMP_BUF)))
		stream->state = -2;
	ft_push_history(stream, stream->config);
	ft_flush(stream);
	while (len--)
		ft_mvright(stream);
}
