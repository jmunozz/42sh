#include "minishell.h"

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t	i;
	size_t	j;

	ft_goend(stream);
	stream->tput = tgetstr("do", NULL);
	ft_tputs(stream);
	stream->tput = tgetstr("le", NULL);
	i = (stream->pos + stream->config->prompt_len) % stream->col;
	j = 0;
	while (j++ < i)
		ft_tputs(stream);
	stream->tput = tgetstr("dl", NULL);
	ft_tputs(stream);
	ft_putstr(mess);
	j = ft_strlen(mess);
	stream->tput = tgetstr("up", NULL);
	ft_tputs(stream);
	stream->tput = tgetstr((j > i ? "le" : "nd"), NULL);
	while (j != i)
	{
		ft_tputs(stream);
		(j > i ? --j : ++j);
	}
	return (0);
}

static char	*ft_gonext(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		if (*str == '\\')
			++str;
		++str;
	}
	return (NULL);
}

int			ft_quotecheck(t_stream *stream)
{
	char	*c;
	t_coord	par;

	ft_bzero(&par, sizeof(t_coord));
	c = stream->command;
	while (*c)
	{
		if ((*c == '\"' || *c == '\'') && !(c = ft_gonext(c + 1, *c)))
			return (ft_underline_mess(QUOTE_ERR, stream));
		if (*c == '[' || *c == ']')
			par.x += (*c == '[' ? 1 : -1);
		else if (*c == '(' || *c == ')')
			par.y += (*c == '(' ? 1 : -1);
		else if (*c == '{' || *c == '}')
			par.z += (*c == '{' ? 1 : -1);
		else if (*c == '\\' && !*(c + 1))
			return (ft_underline_mess(BACK_ERR, stream));
		else if (*c == '\\')
			++c;
		++c;
	}
	if (par.x || par.y || par.z)
		return (ft_underline_mess(PAR_ERR, stream));
	return (1);
}
