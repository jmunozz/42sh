#include "minishell.h"

static void	ft_putmess(t_stream *stream, char *mess)
{
	size_t			i;

	ft_putstr(mess);
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr(" ");
		stream->tput = "le";
		ft_tputs(stream);
	}
	stream->tput = "le";
	i = stream->col;
	while (i--)
		ft_tputs(stream);
	i = ft_strlen(mess) / stream->col + 1;
	stream->tput = "up";
	while (i--)
		ft_tputs(stream);

}

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t			i;
	unsigned int	pos_buf;

	pos_buf = stream->pos;
	ft_goend(stream);
	stream->tput = "do"; // move the cursor one line down
	ft_tputs(stream);
	stream->tput = "le"; // move the cursor left one column
	i = stream->col;
	while (i--)
		ft_tputs(stream);
	stream->tput = "cd"; //clear line cursor and all lines below.
	ft_tputs(stream);
	ft_putmess(stream, mess);
	if (stream->command)
		i = stream->config->prompt_len + ft_strlen(stream->command);
	else
		i = stream->config->prompt_len;
	i = i % stream->col;
	stream->tput = "nd";
	while (i--)
		ft_tputs(stream);
	ft_gomatch(stream, pos_buf, ft_mvleft);
	return (0);
}
