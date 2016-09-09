#include "minishell.h"

void	ft_signal_handle(int i)
{
		if (i == SIGWINCH)
			ft_winsize();
}

void		ft_sigwinch(void)
{
	signal(SIGWINCH, &ft_signal_handle);
}
