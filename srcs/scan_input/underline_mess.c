#include "minishell.h"

static void	ft_replacecursor(t_stream *stream, size_t pos_buf)
{
	stream->tput = "rc";
	ft_tputs(stream);
	ft_prompt(stream->config);
	stream->pos = 0;
	while (stream->pos < pos_buf)
		ft_mvright(stream);
}

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t	i;
	size_t	j;
	size_t	pos_buf;

	pos_buf = stream->pos;
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
	ft_replacecursor(stream, pos_buf);
	return (0);
}
