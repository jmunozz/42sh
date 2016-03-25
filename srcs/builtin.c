#include "minishell.h"

static void	ft_clean_path(char *path)
{
	int		j;

	j = 0;
	while (path && path[j])
	{
		if (path[j] == '/' && path[j + 1] == '.' && path[j + 2] == '/')
			ft_strcpy(path + j, path + j + 2);
		if (path[j] == '/' && path[j + 1] == '.' && path[j + 2] == '.'
				&& j - 2 > 0 && path[j - 1] != '/' && path[j - 2] != '.')
		{
			while (--j != 0 && path[j] != '/');
			ft_strcpy(path + j + (path[j] == '/' ? 1 : 0),
					ft_strchr(path + j + 1, '/') + 3);
		}
		j++;
	}
}

static void	ft_cd(char **argv, t_config *config)
{
	char	*path;
	int		i;

	i = (ft_strcmp(argv[0], "cd") ? 0 : 1);
	if (!argv[i] && (path = ft_strtabfind(config->env, "HOME=")))
		path = ft_strdup(path + 5);
	else if (argv[i] && argv[i][0] == '/')
		path = ft_strdup(argv[i]);
	else if (argv[i] && (path = ft_strtabfind(config->env, "PWD")))
		path = ft_strslashjoin(path + 4, argv[i]);
	if (path)
	{
		ft_clean_path(path);
		if (ft_access_dir(path) && !chdir(path))
			FT_PUTSTRFD("minishell: chdir error through: ", path, "\0", 2);
//		else
//			ft_setenv("PWD", path);
		free(path);
	}
	else
		ft_putstr_fd("minishell: cd: path error, env might be corrupted", 2);
}

static void	ft_env(char **argv, t_config *config)
{
	if (!argv[1])
		ft_putstrtab((char const **)(config->env), '\n');
}

static void	ft_pwd(char **argv, char *pwd)
{
	if (argv[1])
		ft_putstr_fd("pwd: too many arguments", 2);
	else if (!pwd)
		ft_putstr_fd("pwd: path in env is corrupted", 2);
	else
		ft_putstr(pwd + 4);
}

int			ft_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "exit"))
		ft_kill_father(config);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argv, ft_strtabfind(config->env, "PWD"));
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argv, config);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, config);
	else
		return (0);
	return (1);
}
