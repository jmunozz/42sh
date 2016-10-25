#include "minishell.h"

static void	ft_putmess(t_stream *stream, char *mess)
{
	size_t			i;

	ft_putstr(mess);//ecrit le message
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr(" ");
		stream->tput = "le";
		ft_tputs(stream);
	}
	stream->tput = "le"; //move the cursor left one column
	i = stream->col; 
	while (i--)
		ft_tputs(stream);
	i = ft_strlen(mess) / stream->col + 1; // trouve le nb de lignes ecrites
	stream->tput = "up"; //remonte le curseur d'une ligne
	while (i--)
		ft_tputs(stream); //replace le curseur sur la bonne ligne

}

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t			i;
	unsigned int	pos_buf;

	pos_buf = stream->pos; //sauvegarde la pos sur stream (modifiee dans go_end)
	ft_goend(stream); // va jusqu'a la fin de la ligne
	stream->tput = "do"; // move the cursor one line down
	ft_tputs(stream);
	stream->tput = "le"; // move the cursor left one column
	i = stream->col // nb de colonnes dans le terminal
	while (i--)
		ft_tputs(stream);
	stream->tput = "cd"; //clear line cursor and all lines below.
	ft_tputs(stream);
	ft_putmess(stream, mess);
	if (stream->command)
		i = stream->config->prompt_len + ft_strlen(stream->command);
	else
		i = stream->config->prompt_len;
	i = i % stream->col; // calcule le nb de colonnes ecrites sur la derniere ligne
	stream->tput = "nd"; //move the cursor right one column 
	while (i--)
		ft_tputs(stream); //retourn au bout la ligne
	ft_gomatch(stream, pos_buf, ft_mvleft); //replace le curseur a sa place d'origine
	return (0);
}
