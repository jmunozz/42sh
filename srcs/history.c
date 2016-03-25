#include "minishell.h"

void	ft_push_history(char *command, t_config *config)
{
	static short	i = 0;

	if (command && *command)
	{
		if (config->history[i])
			free(config->history[i]);
		config->history[i] = command;
	}
	if (i < 254)
		i++;
	else
		i = 0;
}
