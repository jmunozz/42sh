#include "minishell.h"

static t_list	*ft_quote_replace(char	**t, t_list *next)
{
	int			i;
	size_t		j;

	i = -1;
	while (t[++i])
	{
		j = -1;
		while (t[i][++j])
		{
			if (t[i][j] == '\'' || t[i][j] == '\"')
			{
				ft_memmove(t[i] + j, t[i] + j + 1, ft_strlen(t[i] + j));
				--j;
			}
			else if (t[i][j] == '\\')
				ft_memmove(t[i] + j, t[i] + j + 1, ft_strlen(t[i] + j));
		}
	}
	return (next);
}

t_list			*ft_quote_handle(t_list *next, t_config *config)
{
	char		**t;
	int			i;
	size_t		j;

	t = (char **)next->data;
	i = -1;
	while (t[++i])
	{
		j = 0;
		while (t[i][j])
		{
			if ((t[i][j] == '~' || t[i][j] == '$')
				&& !(t[i] = ft_envvarinsert(t[i], &j, config)))
				return NULL;
			else if (t[i][j] == '\'')
				j = ft_dodge_quote(t[i], j);
			else if (t[i][j] == '\\')
				j += 2;
			else
				++j;
		}
	}
	return (ft_quote_replace(t, next));
}
