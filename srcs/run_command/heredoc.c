
#include "minishell.h"

void	ft_heredoc(char *cmd, size_t *i, t_list **next)
{
	next = NULL;
	while (ft_isspace(*(cmd + ++(*i))));
	ft_putstr(cmd + *i);
	return ;
}