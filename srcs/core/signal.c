#include "minishell.h"

int	ft_signal(void)
{
//	if (SIG_ERR == signal(SIGINT, SIG_IGN))
//		return (ft_status(1));
//	if (SIG_ERR == signal(SIGTSTP, SIG_IGN))
//		return (ft_status(1));
	return (0);
}

void	ft_signal_handle(int i)
{
		if (i == SIGWINCH)
			ft_winsize();
}

void		ft_sigwinch(void)
{
	signal(SIGWINCH, &ft_signal_handle);
}
