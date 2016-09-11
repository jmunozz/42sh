#include "minishell.h"

t_stream	*ft_save_stream(t_stream *stream)
{
	static t_stream	*saved = NULL;

	if (stream)
		saved = stream;
	return (saved);
}

void ft_prompt_reset(t_stream *stream)
{
	size_t			col;
	size_t			i;
	struct winsize	w;

	ioctl(stream->fd, TIOCGWINSZ, &w);
	col = w.ws_col;
	if (stream->col)
	{
		i = (stream->config->prompt_len + stream->pos) / stream->col;
		stream->tput = "up";
		while (i--)
			ft_tputs(stream);
		i = stream->col;
		stream->tput = "le";
		while (i--)
			ft_tputs(stream);
		stream->tput = "cd";
		ft_tputs(stream);
	}
	stream->col = col;
	ft_prompt(stream->config);
}

void		ft_winsize(void)
{
	t_stream		*stream;

	stream = ft_save_stream(NULL);
	ft_prompt_reset(stream);
	if (stream->command)
	{
		stream->pos = 0;
		ft_flushend(stream);
	}
	ft_sigwinch();
}
