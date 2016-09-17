#include "minishell.h"

static char		*ft_isop(char c)
{
	static char	t[] = "<>|;()&#";

	return (ft_strchr(t, c));
}

static size_t	ft_reduc(size_t *i, size_t j)
{
	*i -= j;
	return (0);
}

size_t			ft_match_op(char *cmd, size_t *i)
{
	size_t	op;
	char	buf[8];
	size_t	j;

	j = 0;
	ft_bzero(&buf, 8);
	buf[j] = cmd[*i];
	while (ft_isop(cmd[++(*i)]))
	{
		++j;
		if (j == 1 && ft_isdigit(buf[0]) && (cmd[*i] == '>' || cmd[*i] == '<'))
			buf[j] = cmd[*i];
		else if (cmd[*i] != buf[j - 1] && !(cmd[*i + 1] = 0))
			return (ft_reduc(i, j));
		else if (j == 2 && !ft_isdigit(buf[0]) && cmd[*i] == '<')
			buf[j] = cmd[*i];
		else if (j == 2 && ft_isdigit(buf[0])
			&& (cmd[*i] == '<' || cmd[*i] == '>'))
			buf[j] = cmd[*i];
		else if ((j == 2 || j == 3) && !(cmd[*i] = 0))
			return (ft_reduc(i, j));
	}
	op = (size_t)buf;
	return (op);
}
