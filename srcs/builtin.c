#include "minishell.h"

int		ft_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "exit"))
		ft_kill_father(config);
	else
		return (0);
	return (1);
}
