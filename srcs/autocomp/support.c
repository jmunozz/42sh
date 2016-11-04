#include "../includes/autocomp.h"

void		get_pad(t_stream *stream, char *str)
{
	size_t	size;

	if ((size = ft_strlen(str)) > COMP_PAD)
		COMP_PAD = size;
}

void		init_comp(t_stream *stream)
{
	stream->comp = (t_comp*)malloc(sizeof(t_comp));
	COMP_PAD = 0;
	COMP_COL = stream->col;
	COMP_SIZE_LIST = 0;
	COMP_BEGIN_LIST = NULL;
}
