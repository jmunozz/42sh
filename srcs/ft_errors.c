# includes "minishell.h"

int		ft_prompt_error(t_config *config)
{
	ft_free_config(config);
	ft_putstr_fd("minishell: prompting command error", 2);
	return (1);
}

int		ft_fork_error(t_config *config, char **command)
{
	ft_free_config(config);
	ft_strtabfree(command);
	ft_putstr_fd("minishell: forking error", 2);
	return (1);
}
