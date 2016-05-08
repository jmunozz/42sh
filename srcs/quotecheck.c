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

static int	ft_par(char c)
{
	static int	cro = 0;
	static int	par = 0;
	static int	acc = 0;
	int			ret;

	ret = 0;
	if (!c)
	{
		if (cro | par | acc)
			++ret;
		cro = 0;
		acc = 0;
		par = 0;
	}
	else if (c == '[' || c == ']')
		cro += (c == '[' ? 1 : -1);
	else if (c == '(' || c == ')')
		par += (c == '(' ? 1 : -1);
	else if (c == '{' || c == '}')
		acc += (c == '{' ? 1 : -1);
	return (ret);
}

int			ft_quotecheck(t_stream *stream)
{
	char	*c;

	ft_par(0);
	c = stream->command;
	while (*c)
	{
		ft_par(*c);
		if ((*c == '\"' || *c == '\'') && !(c = ft_gonext(c + 1, *c)))
			return (ft_underline_mess(QUOTE_ERR, stream));
		if (*c == '\\' && !*(c + 1))
			return (ft_underline_mess(BACK_ERR, stream));
		if (*c == '#' && !ft_par(0))
			return (1);
		if (*c == '#')
			return (ft_underline_mess(PAR_ERR, stream));
		if (*c == '\\')
			++c;
		++c;
	}
	if (ft_par(0))
		return (ft_underline_mess(PAR_ERR, stream));
	return (1);
}
