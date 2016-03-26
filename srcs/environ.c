#include "minishell.h"

void	ft_setenv(char *name, char *value, t_config *config)
{
	int		i;
	char	**f;
	char 	*memo;

	f = config->env;
	if ((i = ft_strtabifindstart(f, name)) >= 0 
		&& (memo = f[i])
		&& !(f[i] = ft_strchrjoin(name, '=', value))
		&& (f[i] = memo))
		FT_PUTSTRFD("minishell: error while setenv for: ", name, "\n", 2);
	else if (i >= 0 && !ft_strcmp(name, "PWD"))
	{
		ft_setenv("OLD_PWD", memo + 4, config);
		free(memo);
	}
	else if (!(memo = ft_strchrjoin(name, '=', value)))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ", name, "\n", 2);
	else if (!(config->env = ft_strtabadd(f, memo))
		&& ft_freegiveone((void **)&memo) && (config->env = f))
		FT_PUTSTRFD("minishell: malloc error during setenv for: ", name, "\n", 2);
	else
		ft_strtabfree(f);
}

void	ft_env(char **argv, t_config *config)
{
	if (!argv[1])
		ft_putstrtab((char const **)(config->env), '\n');
	ft_putchar('\n');
}
