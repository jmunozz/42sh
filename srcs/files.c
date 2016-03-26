#include "minishell.h"

int		ft_access_dir(char const *path)
{
	char		*cpy;
	char		*endl;
	struct stat	buf;

	if (!(cpy = ft_strdup(path)))
		return (ft_malloc_error(path));
	endl = cpy;
	while ((endl = ft_strchr(endl + 1, '/')))
	{
		*endl = '\0';
		if (-1 == access(cpy, F_OK) && !(endl = NULL))
			FT_PUTSTRFD("minishell: directory doesn't exist: ", cpy, "\n", 2);
		else if (-1 == stat(cpy, &buf) && !(endl = NULL))
			FT_PUTSTRFD("minishell: stat failed on: ", cpy, "\n", 2);
		else if (!S_ISDIR(buf.st_mode) && !(endl = NULL))
			FT_PUTSTRFD("minishell: ", cpy, ": not a directory\n", 2);
		else if (-1 == access(cpy, X_OK) && !(endl = NULL))
			FT_PUTSTRFD("minishell: permission denied: ", cpy, "\n", 2);
		if (!endl && ft_freegiveone((void **)&cpy))
			return (0);
		*endl = '/';
	}
	return (ft_freegiveone((void **)&cpy));
}

void	ft_access_exec(char *path, char **argv, t_config *config)
{
	struct stat	buf;

	if (!ft_access_dir(path))
		return ;
	if (-1 == access(path, F_OK))
		FT_PUTSTRFD("minishell: command not found:", path, "\n", 2);
	else if (-1 == stat(path, &buf))
		FT_PUTSTRFD("minishell: access denied: ", path, "\n", 2);
	else if (S_ISDIR(buf.st_mode))
		ft_cd(argv, config);
	else if (!S_ISREG(buf.st_mode))
		FT_PUTSTRFD("minishell: ", path, ": not a regular file\n", 2);
	else if (-1 == access(path, X_OK))
		FT_PUTSTRFD("minishell: ", path, ": permission denied\n", 2);
	else
		ft_fewef(path, argv, config->env);
}
