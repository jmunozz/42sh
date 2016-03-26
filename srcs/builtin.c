#include "minishell.h"

static void	ft_clean_path(char *path)
{
	int		i;

	i = 0;
	while (path && path[i])
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/')
			ft_strcpy(path + i, path + i + 2);
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.'
				&& i - 2 > 0 && path[i - 1] != '.' && path[i - 2] != '.')
		{
			while (--i != 0 && path[i] != '/');
			ft_strcpy(path + i + 1, ft_strchr(path + i + 1, '/') + 3);
		}
		if (path[i] == '/'&& path[i + 1] == '/')
			ft_memmove(path, path + 1, strlen(path));
		i++;
	}
	if (path && i && path[i - 1] == '/')
		path[i - 1] = '\0';
}

static void	ft_cd(char **argv, t_config *config)
{
	char	*path;
	int		i;

	path = NULL;
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
		if (ft_access_dir(path) && chdir(path))
			FT_PUTSTRFD("minishell: chdir error through: ", path, "\n", 2);
		else
			ft_setenv("PWD", path, config);
		free(path);
	}
	else
		ft_putstr_fd("minishell: cd: path error, env might be corrupted\n", 2);
}

static void	ft_pwd(char **argv, char *pwd)
{
	if (argv[1])
		ft_putstr_fd("pwd: too many arguments\n", 2);
	else if (!pwd)
		ft_putstr_fd("pwd: path in env is corrupted\n", 2);
	else
		ft_putendl(pwd + 4);
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
