/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 10:09:22 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:04:51 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_mallocenv(char **cmd_split)
{
	char	*env_variable;
	char	*buf;

	if ((env_variable = ft_strdup(*(cmd_split + 1))))
	{
		buf = env_variable;
		if ((env_variable = ft_strjoin(env_variable, "=")))
		{
			free(buf);
			buf = env_variable;
			if ((env_variable = ft_strjoin(env_variable, *(cmd_split + 2))))
			{
				free(buf);
				return (env_variable);
			}
			return (buf);
		}
	}
	return (NULL);
}

static void	ft_modifyenv(t_conf *config, int index, char **cmd_split)
{
	char *env_var;

	if ((env_var = ft_mallocenv(cmd_split)))
	{
		free(config->env[index]);
		config->env[index] = env_var;
	}
}

static void	ft_addenv(t_conf *config, char **cmd_split)
{
	char	*env_var;
	size_t	size_env;
	char	**new_env;
	char	**env_buf;

	if ((env_var = ft_mallocenv(cmd_split)))
	{
		size_env = ft_splitsize(config->env) + 1;
		if ((new_env = ft_fillenv(config->env, size_env)))
		{
			new_env[size_env] = NULL;
			new_env[size_env - 1] = env_var;
			env_buf = config->env;
			config->env = new_env;
			ft_free_split(env_buf);
			free(env_buf);
		}
	}
}

void		ft_setenv(t_conf *config, char **cmd_split)
{
	size_t	splitsize;
	int		i_found;

	i_found = -1;
	if (!(*(cmd_split + 1)))
	{
		ft_printenv(config->env);
		return ;
	}
	if ((splitsize = ft_splitsize(cmd_split)) > 3)
	{
		ft_error(*cmd_split, MANY_ARG, KEEP);
		return ;
	}
	if ((i_found = ft_findenv(config->env, *(cmd_split + 1))) != -1)
		ft_modifyenv(config, i_found, cmd_split);
	else
		ft_addenv(config, cmd_split);
}
