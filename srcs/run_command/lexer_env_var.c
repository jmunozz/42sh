#include "minishell.h"

static char		*ft_isop(char c)
{
	static char	*str = "><|&;`\\()[]{}'\"#";

	return (ft_strchr(str, c));
}

static char	*ft_varsearch(char *cmd, size_t *i, t_config *config, char *m)
{
	char	c;
	char	*e;

	while (cmd[*i] && !ft_isop(cmd[*i]))
		++(*i);
	c = cmd[*i];
	cmd[*i] = 0;
	e = ft_strtabfind(config->env, m);
	cmd[*i] = c;
	return (e);
}

char		*ft_envvarinsert(char *cmd, size_t *i, t_config *config)
{
	char	*m;
	char	*e;

	if (ft_isop(cmd[*i + 1]))
		return (cmd);
	m = cmd + *i + 1;
	if (cmd[*i] == '~')
	{
		if (*i || cmd[1])
			return (cmd);
		e = ft_strtabfind(config->env, "HOME=");
		if (e)
			e += 5;
	}
	else
		e = ft_varsearch(cmd, i, config, m);
	ft_memmove((void *)(m - 1), (void *)(cmd + *i), ft_strlen(cmd + *i));
	*i = m - 1 - cmd + ft_strlen(e);
	if (e && (e = ft_strinsert(cmd, e, m - 1)) && ft_freegiveone((void**)&cmd))
		return (e);
	return (NULL);
}
