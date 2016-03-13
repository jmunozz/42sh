#include "minishell.h"

static int		ft_initerror(void)
{
		ft_putstr_fd("minishell: init error", 2);
		return (1);
}

int		main(char **env)
{
	t_config	*config;
	int			i;

	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
		return (ft_initerror());
	if (!(config->env = ft_strtabdup(env)))
	{
		free(config);
		return (ft_initerror());
	}
	if (!(config->prompt = ft_strdup("&> ")))
	{
		ft_strtabfree(config->env);
		free(config);
		return (ft_initerror());
	}
	return (ft_minishell(config));
}
