#include "minishell.h"

static char		*ft_isop(char c)
{
	static char	t[] = "<>|;()&#";

	return (ft_strchr(t, c));
}

static char		*ft_reduc(size_t *i, size_t j)
{
	*i -= j;
	return (NULL);
}

static char		*ft_agregation(char *buf, size_t *i, char *cmd, size_t *j)
{
	while (ft_isop(cmd[*i]))
	{
		if (*j > 3)
			return (ft_reduc(i, *j));
		if (*j == 3 && cmd[*i] != '&')
			return (ft_reduc(i, *j));
		buf[*j] = cmd[*i];
		(*i)++;
		(*j)++;
	}
	if (ft_isdigit(cmd[*i]))
	{
		buf[(*j)] = cmd[(*i)];
		(*i)++;
	}
	return (ft_strdup(buf));
}

char			*ft_match_op(char *cmd, size_t *i)
{
	char	buf[8];
	size_t	j;

	j = 0;
	ft_bzero(&buf, 8);
	buf[j] = cmd[*i];
	while (ft_isop(cmd[++(*i)]))
	{
		++j;
		if (j == 1 && ft_isdigit(buf[0]) && (cmd[*i] == '>' || cmd[*i] == '<'))
			return (ft_agregation((char*)buf, i, cmd, &j));
		else if (cmd[*i] != buf[j - 1] && !(cmd[*i + 1] = 0))
			return (ft_reduc(i, j));
		else if ((j >= 2) && !(cmd[*i] = 0))
			return (ft_reduc(i, j));
		else
			buf[j] = cmd[*i];
	}
	return (ft_strdup(buf));
}
