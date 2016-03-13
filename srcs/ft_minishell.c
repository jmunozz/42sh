# include "minishell.h"

int		ft_free_error(t_config *config)

int		ft_minishell(t_config *config)
{
	pid_t	father;

	ft_putstr(config->prompt);
	if (0 > (father = fork())
		return (ft_fork_error(config));
}
