#include "minishell.h"

static int		ft_initerror(void)
{
		ft_putstr_fd("minishell: init error", 2);
		return (1);
}

int		main(int ac, char **av, char **env)
{
	t_config	*config;
	int			i;

	if (!(config = (t_config *)ft_memalloc(sizeof(t_config))))
		return (ft_initerror());
	if (!(config->env = ft_strtabdup(env)) && ft_freegiveone(config))
		return (ft_initerror());
	if (!(ft_prompt(ft_strtabfind(config->env))))
	{
		ft_strtabfree(config->env);
		free(config);
		return (ft_initerror());
	}
	ft_putstr(config->prompt);
	ft_minishell(config);
	return (ft_status(0));
}
