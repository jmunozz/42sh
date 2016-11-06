#include "../../includes/minishell.h"

/*
static void	ft_putmess(t_stream *stream, char *mess)
{
	size_t			i;

	ft_putstr(mess); //imprime le message.
	// si le curseur n'est pas sur la derniere colonne
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr(" "); //impression
		stream->tput = "le"; //puis un pas en arriere
		ft_tputs(stream);
	}
	stream->tput = "le";
	i = stream->col;
	while (i--)
		ft_tputs(stream); //permet de revenir sur le premier élément de la ligne.
	//On remonte le nombre de lignes imprimées + 1 pour celle sautée initialement.
	i = ft_strlen(mess) / stream->col + 1; // Version Toussaint.
	//i = COMP_ELEM_IN_COL + 1; // Version Jordan
	stream->tput = "up";
	while (i--)
		ft_tputs(stream);

}*/

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t			i;
	unsigned int	pos_buf;

	mess = NULL;
	pos_buf = stream->pos;
	ft_goend(stream); //on va au bout de la ligne de commande.
	stream->tput = "do"; //on saute une ligne.
	ft_tputs(stream);
	stream->tput = "le";
	i = stream->col;
	while (i--)
		ft_tputs(stream); //ATTENTION peut-être une incohérence.
	stream->tput = "cd"; //clear line cursor and all lines below.
	ft_tputs(stream);
	ft_print_autocomp(stream);
	if (stream->command)
		i = stream->config->prompt_len + ft_strlen(stream->command); // i = prompt + commande
	else
		i = stream->config->prompt_len; // si pas de comande i = prompt
	i = i % stream->col; // retranche ce qui est du à la présence de plusieurs lignes.
	stream->tput = "nd";
	while (i--)
		ft_tputs(stream); //on se retrouve sur le dernier caractère de la ligne de commande.
	ft_gomatch(stream, pos_buf, ft_mvleft); //on remonte jusqu'au caractère enregistré.
	return (0);
}
