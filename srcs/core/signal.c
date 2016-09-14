#include "minishell.h"

void		ft_signal_handle(int i)
{
	if (i == SIGWINCH)
		ft_winsize();
	if (i == SIGINT)
		++i;
	if (i == SIGTSTP)
		++i;
	ft_signal();
}

void		ft_sigwinch(int mode)
{
	if (mode && SIG_ERR == signal(SIGWINCH, &ft_signal_handle))
		ft_putstr_fd("minishell: sigwinch fail\n", 2);
	else if (!mode && SIG_ERR == signal(SIGWINCH, SIG_DFL))
		ft_putstr_fd("minishell: sigwinch fail\n", 2);
}

void		ft_signal_reset(void)
{
	if (SIG_ERR == signal(SIGINT, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
		ft_status(1);
}

int			ft_signal(void)
{
	if (SIG_ERR == signal(SIGINT, &ft_signal_handle))
		return (ft_status(1));
	if (SIG_ERR == signal(SIGTSTP, &ft_signal_handle))
		return (ft_status(1));
	return (0);
}
