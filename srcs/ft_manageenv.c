/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 10:57:15 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/27 16:19:53 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_fillenv(char **env, size_t size)
{
	char	**env_cpy;
	size_t	i;

	i = 0;
	if ((env_cpy = (char**)ft_memalloc(sizeof(*env) * (size + 1))))
	{
		while (i < size && *env)
		{
			env_cpy[i] = ft_strdup(*env);
			i++;
			env++;
		}
		env_cpy[i] = NULL;
	}
	return (env_cpy);
}

char	**ft_parseenv(char **env, char *name)
{
	char	**split;

	while (*env)
	{
		if ((split = ft_strsplit(*env, '=')))
		{
			if (*split && ft_strcmp(split[0], name) == 0)
				return (split);
			ft_free_split(split);
			free(split);
		}
		env++;
	}
	return (NULL);
}

int		ft_findenv(char **env, char *variable)
{
	int		ret;
	int		i;
	char	**split;

	ret = -1;
	i = 0;
	while (env && *env)
	{
		if ((split = ft_strsplit(*env, '=')))
		{
			if (ft_strcmp(split[0], variable) == 0)
				ret = i;
			ft_free_split(split);
			free(split);
			if (ret != -1)
				return (ret);
		}
		i++;
		env++;
	}
	return (-1);
}

void	ft_printenv(char **env)
{
	while (env && *env)
	{
		ft_putstr(*env);
		ft_putchar('\n');
		env++;
	}
}
