#include "minishell.h"

int		ft_access_dir(char const *path)
{
	char		*cpy;
	char		*endl;
	struct stat	buf;

	if (!(cpy = ft_strdup(path)))
		return (ft_malloc_error(path));
	endl = cpy;
	while ((endl = ft_strchr(endl, '/')))
	{
		*endl = '\0';
		if (*cpy == '\0');
		else if (-1 == access(cpy, F_OK) && !(endl = NULL))
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
		endl++;
	}
	return (ft_freegiveone((void **)&cpy));
}

void	ft_access_exec(char **argv, char **env)
{
	struct stat	buf;

	if (!ft_access_dir(argv[0]))
		return ;
	if (-1 == access(argv[0], F_OK))
		FT_PUTSTRFD("minishell: command not found:", argv[0], "\n", 2);
	else if (-1 == stat(argv[0], &buf))
		FT_PUTSTRFD("minishell: access denied: ", argv[0], "\n", 2);
//	else if (S_ISDIR(buf.st_mode))
//		ft_cd(argv);
	else if (!S_ISREG(buf.st_mode))
		FT_PUTSTRFD("minishell: ", argv[0], ": not a regular file\n", 2);
	else if (-1 == access(argv[0], W_OK))
		FT_PUTSTRFD("minishell: ", argv[0], ": permission denied\n", 2);
	else
		ft_fewef(argv[0], argv, env);
}
