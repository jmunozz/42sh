#include "../../includes/autocomp.h"
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
** Imprime une ligne élément par élément.
** Imprime un élément puis l'élément n + COMP_IN_COL de manière récursive.
*/
void		ft_autocomp_print_line(t_list *list, size_t elem, t_stream *stream)
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
** Imprime une ligne. Assure le retour à la ligne et la bonne incrémentation de la liste.
*/
void		ft_autocomp_print_grid(size_t start, size_t end, t_stream *stream)
{
	size_t	j;
	t_list	*list;

	list = COMP_BEGIN_LIST;
	j = -1;
	while (++j < start)
		list = list->next;
	while (start < end)
	{
		ft_autocomp_print_line(list, start, stream);
		stream->tput = "le";
		j = COMP_COL;
		while (j--)
			ft_tputs(stream);
		stream->tput = "do";
		if (start != end - 1)
			ft_tputs(stream);
		list = list->next;
		start++;
	}
}
/*
** N'imprime que la partie de la liste imprimable et gère le scroll vertical.
*/
void		ft_autocomp_scroll(t_stream *stream)
{
	static int		start = 0;
	int				current;
	int				end;

	current = (int)COMP_CURRENT;
	while (current - (int)COMP_IN_COL > 0 || (current == (int)COMP_IN_COL))
		current -= COMP_IN_COL;
	end = start + COMP_DISPLAYABLE;
	if (current < start)
	{
		start = current;
		end = start + COMP_DISPLAYABLE;
	}
	else if (current >= end)
	{
		end = current + 1;
 		start = end - COMP_DISPLAYABLE;
	}
	ft_autocomp_print_grid(start, end, stream);
	ft_repeat_termcaps((end - start + 1), "up", stream);
	ft_autocomp_underline(stream, 'U');
}
/*
** Fonction intermédiaire.
** Si oversize, imprime le prompt en dessous. Sinon remonte le nombre de lignes imprimées.
*/
void		ft_comp_print(t_stream *stream)
{
	//size_t i;

	get_col_elem(stream); // obtient COMP_IN_COL.
	ft_autocomp_underline(stream, 'D'); //Positionne le curseur en dessous de la ligne de commande.
	if (ft_autocomp_is_oversize(stream))
		if (COMP_STATE == 1)
		{
			ft_autocomp_print_grid(0, COMP_IN_COL, stream);//imprime les colonnes.
			stream->tput = "do";
			ft_tputs(stream);
			ft_winsize();
		}
		else
			ft_autocomp_scroll(stream);
	else
	{
		ft_autocomp_print_grid(0, COMP_IN_COL, stream); //imprime les colonnes.
		ft_repeat_termcaps(COMP_IN_COL, "up", stream);
		ft_autocomp_underline(stream, 'U'); // Positionne le curseur à sa place sur la commande.
	}
}
