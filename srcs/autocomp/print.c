#include "../../includes/autocomp.h"

void		get_col_elem(t_stream *stream)
{
	size_t col_nb;
	col_nb = (COMP_COL + 1) / (COMP_PAD + 1);
	if (COMP_SIZE_LIST > col_nb)
		COMP_IN_COL = !(COMP_SIZE_LIST % col_nb) ? COMP_SIZE_LIST / col_nb : (COMP_SIZE_LIST / col_nb) + 1;
	else
		COMP_IN_COL = 1;
}


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
			ft_putstr(list->data);
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
		j =  COMP_IN_COL;
		while (j--)
			ft_tputs(stream);
	}
}

void		ft_print_autocomp(t_stream *stream)
{

	get_col_elem(stream);
	ft_putstr(list_to_char(stream, COMP_BEGIN_LIST));
	ft_putnbr(COMP_IN_COL);
	ft_print_col(stream); //imprime les colonnes.

}
