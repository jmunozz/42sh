# include "minishell.h"


void	ft_free_config(t_config *config)
{
	ft_strtabfree(config->env);
	free(config->prompt);
	free(config);
}
