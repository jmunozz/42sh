#include "minishell.h"

int		ft_putcharint(int	i)
{
	char		c;

	c = i;
	ft_putchar(c);
	return(c);
}

void			ft_tputs(t_stream *stream)
{
	tputs(stream->tput, stream->fd, &ft_putcharint);
}

void			ft_mvleft(t_stream *stream)
{
	int			i;

	if (stream->pos)
	{
		if ((stream->config->prompt_len + stream->pos) % stream->col)
		{
			stream->tput = tgetstr("le", NULL);
			ft_tputs(stream);
		}
		else
		{
			stream->tput = tgetstr("up", NULL);
			ft_tputs(stream);
			i = -1;
			stream->tput = tgetstr("nd", NULL);
			while ((unsigned int)++i < stream->col)
				ft_tputs(stream);
		}
		stream->pos--;
	}
}

void			ft_mvright(t_stream *stream)
{
	int			i;

	if (stream->command)
	{
		if (((stream->config->prompt_len + stream->pos) % stream->col) != stream->col - 1)
		{
			stream->tput = tgetstr("nd", NULL);
			ft_tputs(stream);
		}
		else
		{
			stream->tput = tgetstr("do", NULL);
			ft_tputs(stream);
			i = -1;
			stream->tput = tgetstr("le", NULL);
			while ((unsigned int)++i < stream->col)
				ft_tputs(stream);
		}
		stream->pos++;
	}
}
