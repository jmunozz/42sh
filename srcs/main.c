#include "minishell.h"

int		main(char **env)
{
	t_config	*config;
	int			i;

	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
	{
		ft_putstr("minishell: init error");
		return (1);
	}
	config->env = ft_strtabdup(env);
	config->prompt = ft_strdup("&> ");
	return (ft_minishell(config));
}
