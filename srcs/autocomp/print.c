#include "../../includes/autocomp.h"
/*
 ** Récupère le nombre d'éléments par colonnes COMP_IN_COL.
 */
void		get_col_elem(t_stream *stream)
{
	size_t col_nb;
	col_nb = (COMP_COL + 1) / (COMP_PAD + 2);
	if (COMP_SIZE_LIST > col_nb)
		COMP_IN_COL = !(COMP_SIZE_LIST % col_nb) ? COMP_SIZE_LIST / col_nb : (COMP_SIZE_LIST / col_nb) + 1;
	else
		COMP_IN_COL = 1;
}
/*
 ** Gère l'impression d'un élément avec le padding approprié. Si data_size = 1, imprime
 ** l'élément en surbrillance.
 */
void		ft_print_elem(t_list *list, t_stream *stream)
{
	if (!list->data_size)
		ft_putstrpad(list->data, COMP_PAD, 'L');
	else
	{
		stream->tput = "mr";
		ft_tputs(stream);
		ft_putstrpad(list->data, COMP_PAD, 'L');
		stream->tput = "me";
		ft_tputs(stream);
	}
}
/*
   void		ft_print_col(t_stream *stream)
   {
   t_list		*list;
   size_t		i;
   size_t		j;
   size_t		k;

   list = COMP_BEGIN_LIST;
   k = 0;
   while (list)
   {
   i = -1;
   while (++i < COMP_IN_COL && list)
   {
   j = k * (COMP_PAD + 2);
   stream->tput = "nd";
   while (j--)
   ft_tputs(stream);
   ft_print_elem(list, stream);
   stream->tput = "do";
   ft_tputs(stream);
   stream->tput = "le";
   j = COMP_COL;
   while (j--)
   ft_tputs(stream);
   list = list->next;
   }
   k++;
   stream->tput = "up";
   if (list)
   j =   COMP_IN_COL;
   else
   j =  !(COMP_SIZE_LIST % COMP_IN_COL) ? COMP_IN_COL + 1 :
   COMP_SIZE_LIST % COMP_IN_COL + 1;
   while (j--)
   ft_tputs(stream);
   }
   }*/
/*
 ** Fonction intermédiaire.
 ** Si oversize, imprime le prompt en dessous. Sinon remonte le nombre de lignes imprimées.
 */
void		ft_print_autocomp(t_stream *stream)
{
	size_t i;

	get_col_elem(stream); // obtient COMP_IN_COL.
	ft_autocomp_underline(stream, 'D'); //Positionne le curseur en dessous de la ligne de commande.
	ft_autocomp_print(stream); //imprime les colonnes.
	if (ft_autocomp_is_oversize(stream))
		ft_winsize();
	else
	{
		stream->tput = "up";
		i = COMP_IN_COL + 1;
		while (i--)
			ft_tputs(stream);
		ft_autocomp_underline(stream, 'U'); // Positionne le curseur à sa place sur la commande.
	}
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
 ** Imprime une ligne. Assure le retour à la ligne et la bonne incrémentation de la liste.
 */
void		ft_autocomp_print(t_stream *stream)
{
	size_t	i;
	size_t	j;
	t_list	*list;

	list = COMP_BEGIN_LIST;
	i = 0;
	while (i < COMP_IN_COL)
	{
		ft_autocomp_print_line(list, i, stream);
		stream->tput = "le";
		j = COMP_COL;
		while (j--)
			ft_tputs(stream);
		stream->tput = "do";
		ft_tputs(stream);
		list = list->next;
		i++;
	}
}
/*
 ** Imprime une ligne élément par élément.
 ** Imprime un élément puis l'élément n + COMP_IN_COL de manière récursive.
 */
void	ft_autocomp_print_line(t_list *list, size_t elem, t_stream *stream)
{
	size_t	new_elem;
	size_t	j;

	ft_print_elem(list, stream);
	if ((new_elem = elem + COMP_IN_COL) < COMP_SIZE_LIST)
	{
		stream->tput = "nd";
		ft_tputs(stream);
		ft_tputs(stream);
		j = COMP_IN_COL;
		while (j--)
			list = list->next;
		ft_autocomp_print_line(list, new_elem, stream);
	}
}
/*
 ** Check si l'impression de la liste dépasse la taille de l'écran.
 */
int		ft_autocomp_is_oversize(t_stream *stream)
{
	size_t	command_size;

	command_size = (stream->config->prompt_len + ft_strlen(stream->command)) % COMP_COL;
	command_size = (command_size) ?
		(stream->config->prompt_len + ft_strlen(stream->command)) / COMP_COL + 1 :
		(stream->config->prompt_len + ft_strlen(stream->command)) / COMP_COL;
	if (COMP_IN_COL > COMP_ROW - command_size)
		return (1);
	return (0);
}

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
		stream->tput = "le";
		i = stream->col;
		while (i--)
			ft_tputs(stream); //ATTENTION peut-être une incohérence.
		stream->tput = "cd"; //clear line cursor and all lines below.
		ft_tputs(stream);
	}
	else
	{
		if (stream->command)
			i = stream->config->prompt_len + ft_strlen(stream->command); // i = prompt + commande
		else
			i = stream->config->prompt_len; // si pas de comande i = prompt
		i = i % stream->col; // retranche ce qui est du à la présence de plusieurs lignes.
		stream->tput = "nd";
		while (i--)
			ft_tputs(stream); //on se retrouve sur le dernier caractère de la ligne de commande.
		ft_gomatch(stream, pos_buf, ft_mvleft); //on remonte jusqu'au caractère enregistré.
	}
}
