
#include "minishell.h"

int		ft_heredocmode(int mode)
{
	static int	status = 0;
	int			tmp;
	
	tmp = status;
	status = mode;
	return (tmp);
}
/*
void	ft_heredoc(t_list *begin)
{
	while (begin && begin->data_size != HEREDOC)
		begin = begin->next;
	if (begin)
	{
		
		ft_heredoc(begin);
	}
	return ;
}
*/
