#include "minishell.h"

static char	**sft_tabdup(char **t, char *m, char c, int nb)
{
	int		i;

	i = 0;
	while (nb--)
	{
		if (!(t[i++] = ft_strdup(m)))
		{
			ft_strtabfree(t);
			return NULL;
		}
		else if (nb)
		{
			m += ft_strlen(m) + 1;
			while (*m == c)
				m++;
		}
	}
	return (t);
}

static char	**ft_strdodgesplit(char *s, char c)
{
	char	**t;
	char	*m;
	int		nb;
	int		i;

	m = s;
	nb = 0;
	while (*s)
	{
		i = 0;
		if (*s == c && *(s - 1) && *(s - 1) != c && !(*s = 0) && ++s)
			nb++;
		else if ((*s == '\'' || *s == '\"') && (i = ft_dodge_quote(s, i)))
			s += i;
		else
			++s;
	}
	nb += ((*(s - 1) && *(s - 1) != c) ? 1 : 0);
	if (!(t = (char **)ft_memalloc(sizeof(char *) * (nb + 1))))
		return NULL;
	return (sft_tabdup(t, m, c, nb));
}

int				ft_dodge_quote(char *cmd, size_t i)
{
	char	c;

	c = cmd[i];
	while (cmd[++i] != c)
		if (cmd[i] == '\\')
			++i;
	return (i + 1);
}

static t_list	**ft_av_handle(char *cmd, size_t i, t_list **next)
{
	char	**t;
	char	c[2];

	c[0] = cmd[i];
	c[1] = 0;
	cmd[i] = 0;
	while (*cmd && *cmd == ' ')
	{
		++cmd;
		--i;
	}
	if (!cmd || !(t = ft_strdodgesplit(cmd, ' ')))
	{
		if (!cmd)
			ft_error(SHNAME, "parse error near", c, CR_ERROR);
		else
			ft_error(SHNAME, "lexer", "malloc error", CR_ERROR);
		return NULL;
	}
	cmd[i] = c[0];
	(*next)->data = (void*)t;
	(*next)->data_size = 0;
	return (next);
}

t_list		*ft_op_handle(char *cmd, size_t *i, t_list **next)
{
	if (!*i && !(cmd[*i + 1] = 0)
		&& ft_error(SHNAME, "parse error near", cmd + *i, CR_ERROR))
		return NULL;
	if (!(next = ft_av_handle(cmd, *i, next)))
		return NULL;
	if (cmd[*i])
	{
		if (!((*next)->next = (t_list *)ft_memalloc(sizeof(t_list)))
			&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR))
			return NULL;
		*next = (*next)->next;
		if (!((*next)->data = (void*)ft_match_op(cmd, i))
			&& ft_error(SHNAME, "parse error near", cmd + *i, CR_ERROR))
			return NULL;
		if (!ft_strcmp((*next)->data, "<<") && ((*next)->data_size = HEREDOC))
			ft_heredocmode(1);
		else
			(*next)->data_size = 1;
	}
	return (*next);
}
