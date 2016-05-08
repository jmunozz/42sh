#include "minishell.h"

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t	i;

	i = ft_strlen(mess);
	ft_goend(stream);
	while ((stream->pos + stream->config->prompt_len) % stream->col)
		ft_left(stream);
	stream->tput = tgetstr("do");
	ft_tputs(stream);
	ft_putstr(mess);
	stream->tput = tgetstr("up");
	ft_tputs(stream);
	stream->tput = tgetstr("le");
	while (i--)
		ft_tputs(stream);
	ft_goend(stream);
	return (0);
}

static char	*ft_gonext(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		if (*str == '\\')
			str += 2;
		else
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
		if ((*c == '"' || *c == ''') && !(c = ft_gonext(c + 1, *c)))
			return (ft_underline_mess(QUOTE_ERR, stream);
		if (*c == '[' || *c == ']')
			par.x += (*c == '[' ? 1 : -1);
		else if (*c == '(' || *c == ')')
			par.y += (*c == '(' ? 1 : -1);
		else if (*c == '{' || *c == '}')
			par.z += (*c == '{' ? 1 : -1);
		else if (*c == '\')
			++c;
		++c;
	}
	if (par.x || par.y || par.z)
		return (ft_underline_mess(PAR_ERR, stream);
	return (1);
}
