#include "minishell.h"

static void	ft_exe_insert(DIR dir, char *path, t_config *config)
{
	t_dirent	*dirent;
	t_exe		exe;
	t_list		*new;

	while (dirent = readdir(dir))
	{
		if (!(exe.path_name = ft_strslashjoin(path, dirent->d_name))
				|| !(exe.name = ft_strrchr(path_name, '/') + 1)
				|| !(new = ft_lstnew(&exe, sizeof(t_exe))))
			ft_putstr_fd("minishell : error creating path to exe", 2);
		else
			ft_lstadd(&(config->exe), new);
	}
}

static int	ft_create_list_exe(char *path, t_config *config)
{
	char	*dirpath;
	char	*kill;
	DIR		dir;

	if(!path || !(path = ft_strchr(path, '=')) || !*(++path)
			|| !(path = ft_strdup(path)))
		return (NULL);
	kill = path;
	while ((dirpath = path))
	{
		path = ft_strchr(path, ':');
		if (path && (++path))
			*(path - 1) = '\0';
		if (dir = opendir(dirpath))
		{
			ft_exe_insert(dir, dirpath, config);
			close(dir);
		}
	}
	free(kill);
}

int			ft_pathtohash(t_config *config)
{
	char	*path;

	if (!(path = ft_strtabfind(config->env, "PATH"))
			|| !(ft_create_list_exe(path, config)))
		return (0);
	ft_lstsort(&(config->exe), &ft_execmp)

}
