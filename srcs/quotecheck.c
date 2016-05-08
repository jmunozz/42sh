#include "minishell.h"

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
	int		cro;
	int		par;
	int		acc;

	par = 0;
	cro = 0;
	acc = 0;
	c = stream->command;
	while (*c)
	{
		if ((*c == '"' || *c == ''') && !(c = ft_gonext(c + 1, *c)))
			return (ft_underline_mess("please end your quote to run command");
		if (*c == '[' || *c == ']')
			cro += (*c == '[' ? 1 : -1);
		else if (*c == '(' || *c == ')')
			par += (*c == '[' ? 1 : -1);
		else if (*c == '{' || *c == '}')
			acc += (*c == '[' ? 1 : -1);
		else if (*c == '\')
			c += 2;
		else
			++c;
	}
	if (par || cro || acc)
		return (ft_underline_mess("missing '(' ')' '{' '}' '[' or ']' to run command");
	return (1);
}
