#include "minishell.h"

t_stream		*ft_save_stream(t_stream *stream)
{
	static t_stream	*saved = NULL;

	if (stream)
		saved = stream;
	return (saved);
}

static size_t	ft_count_line(t_stream *stream)
{
	size_t	lin;
	size_t	pos;
	size_t	col;

	pos = -1;
	col = (stream->config->prompt_len - 1) % stream->col;
	lin = (stream->config->prompt_len - 1) / stream->col;
	if (stream->command)
		while (++pos <= stream->pos)
		{
			++col;
			if (stream->command[pos] == '\n'
				|| col - 1 == stream->col)
			{
				++lin;
				col = 0;
			}
		}
	return (lin);
}

void			ft_prompt_reset(t_stream *stream)
{
	size_t			col;
	struct winsize	w;
	size_t			lin;

	ioctl(stream->fd, TIOCGWINSZ, &w);
	col = w.ws_col;
	if (stream->col)
	{
		lin = ft_count_line(stream);
		stream->tput = "up";
		while (lin--)
			ft_tputs(stream);
		stream->tput = "le";
		while ((stream->col)--)
			ft_tputs(stream);
		stream->tput = "cd";
		ft_tputs(stream);
	}
	stream->col = col;
	ft_prompt(stream->config);
}

void			ft_winsize(void)
{
	t_stream		*stream;
	unsigned int	pos;

	stream = ft_save_stream(NULL);
	ft_prompt_reset(stream);
	if (stream->command)
	{
		pos = stream->pos;
		stream->pos = 0;
		ft_flushend(stream);
		ft_gomatch(stream, pos, ft_mvleft);
	}
	ft_sigwinch(1);
}
