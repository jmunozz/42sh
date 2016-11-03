
#include "minishell.h"

int		ft_heredocmode(int mode)
{
	static int	status = 0;
	int			tmp;
	
	tmp = status;
	status = mode;
	return (tmp);
}

void	ft_heredoc(t_list *begin, t_config *config)
{
	while (begin && begin->data_size != HEREDOC)
		begin = begin->next;
	if (begin && begin->next)
	{
		config->heredoc = (char*)begin->next->data;
		ft_heredoc(begin, config);
	}
	return ;
}
