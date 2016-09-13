#include "minishell.h"

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t	i;
	size_t	j;

	ft_goend(stream);
	stream->tput = "do";
	ft_tputs(stream);
	stream->tput = "le";
	i = (stream->pos + stream->config->prompt_len) % stream->col;
	j = 0;
	while (j++ < i)
		ft_tputs(stream);
	stream->tput = "dl";
	ft_tputs(stream);
	ft_putstr(mess);
	j = ft_strlen(mess);
	stream->tput = "up";
	ft_tputs(stream);
	stream->tput = (j > i ? "le" : "nd");
	while (j != i)
	{
		ft_tputs(stream);
		(j > i ? --j : ++j);
	}
	return (0);
}
