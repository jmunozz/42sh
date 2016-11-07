#include "minishell.h"

static char		*ft_isop(char c)
{
	static char	t[] = "<>|;&#()";

	return (ft_strchr(t, c));
}

static char		*ft_reduc(size_t *i, size_t j, char *buf, char *cmd)
{
	*i -= j;
	if (buf)
		ft_error(SHNAME, "lexer error, operator too long", buf, CR_ERROR);
	else
		ft_error(SHNAME, "parse error near", cmd + *i, CR_ERROR);
	return (NULL);
}

static char		*ft_agregation(char *buf, size_t *i, char *cmd, size_t *j)
{
	while (ft_isdigit(cmd[*i]) && (*j < 256))
		buf[(*j)++] = cmd[(*i)++];
	buf[(*j)++] = cmd[(*i)++];
	if (((cmd[*i - 1] == '>' && cmd[*i] == '>')
		|| (cmd[*i - 1] == '<' && cmd[*i] == '<')) && (*j < 256))
		buf[(*j)++] = cmd[(*i)++];
	if (cmd[*i] != '&' && ft_isop(cmd[*i]) && (cmd[*i + 1] = 0)
		&& (*j < 256))
		return (ft_reduc(i, 0, NULL, cmd));
	else if (*i > 1 && cmd[*i] == '&' && (cmd[*i - 1] == '<'
		|| cmd[*i - 2] == '>' || !ft_isdigit(cmd[*i + 1]))
		&& !(cmd[*i + 1] = 0))
		return (ft_reduc(i, 0, NULL, cmd));
	if (cmd[*i] == '&' && (*j < 256))
		buf[(*j)++] = cmd[(*i)++];
	else
		return (ft_strdup(buf));
	while (ft_isdigit(cmd[*i]) && (*j < 256))
		buf[(*j)++] = cmd[(*i)++];
	if (*j == 256)
		return (ft_reduc(i, 0, buf, cmd));
	return (ft_strdup(buf));
}

char			*ft_match_op(char *cmd, size_t *i)
{
	char	buf[256];
	size_t	j;

	j = 0;
	ft_bzero(&buf, 256);
	buf[j] = cmd[*i];
	if ((ft_isdigit(buf[0]) || buf[0] == '<' || buf[0] == '>'))
		return (ft_agregation((char*)buf, i, cmd, &j));
	while (cmd[++*i] && !ft_strchr("()", cmd[*i]) && ft_isop(cmd[*i]))
	{
		++j;
		if ((cmd[*i] != buf[j - 1] || buf[0] == ';') && !(cmd[*i + 1] = 0))
			return (ft_reduc(i, j, NULL, cmd));
		else if ((j >= 2) && !(cmd[*i] = 0))
			return (ft_reduc(i, j, NULL, cmd));
		else
			buf[j] = cmd[*i];
	}
	if (!cmd[*i] && ft_strchr("<>|", buf[0]))
		return (ft_reduc(i, 1, NULL, cmd));
	return (ft_strdup(buf));
}
