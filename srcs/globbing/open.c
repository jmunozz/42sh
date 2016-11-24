#include "../../includes/minishell.h"

int		is_valid(int i, int j, char *glob, char *file);
void	ft_print_list(t_list *begin);
int		ft_isalphaa(char c);

int		ft_strlencc(char *str, char c)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_glob(DIR *dir, char *path, char *glob, t_list **begin)
{
	char			buf[256];
	struct dirent	*file;
	int				end;

	end = ft_strlen(ft_strcpy(buf, path));
	if (!*glob)
		ft_list_push_back(begin, ft_lstnew(ft_strdup(buf), 0));
	if (dir && *glob == '/')
		ft_glob(dir, ft_strcat(buf, "/"), ++glob, begin);
	else if (dir)
		while ((file = readdir(dir)))
		{
			if (!ft_strcmp(file->d_name, ".") && !ft_strncmp(glob, "**/", 3))
			{
				if (glob[3])
					ft_glob(opendir((!*buf) ? "." : buf), buf, (glob + ft_strlencc(glob, '/') + 1), begin);
				else
					ft_glob(opendir((!*buf) ? "." : buf), buf, (glob + 1), begin);
			}
			if (is_valid(0, 0, glob, file->d_name) && ((ft_strcmp(file->d_name, ".")
			&& ft_strcmp(file->d_name, "..") && (*(file->d_name) != '.' ||
			(*(file->d_name) == '.' && is_valid(0, 0, ".*", glob))))
			|| (is_valid(0, 0, ".", glob) && !ft_strcmp(file->d_name, "."))
			||(is_valid(0, 0, "..", glob) && !ft_strcmp(file->d_name, ".."))))
			{
				if (ft_strcat(buf, file->d_name) && ft_strncmp(glob, "**/", 3))
					ft_glob(opendir(buf), buf, (glob + ft_strlencc(glob, '/')), begin);
				else
					ft_glob(opendir(buf), ft_strcat(buf, "/"), glob, begin);
				ft_bzero(&buf[end], (255 - end));
			}
		}
}

int		main(int ac, char **av)
{
	DIR		*stream;
	int		size;
	t_list	*begin;
	char	buf[256];

	ft_bzero(buf, 256);
	begin = NULL;
	if (ac > 1)
	{
		if (!(size = ft_strlenc(av[1], '/')) && !(stream = opendir("/")))
		{
			printf("L'ouverture de la racine a échoué\n");
			return (0);
		}
		else if (!stream)
		{
			if (!(stream = opendir(".")))
			{
				printf("L'ouvertude du dossier courant  a échoué\n");
				return (0);
			}
		}
		ft_glob(stream, buf, av[1],  &begin);
		ft_print_list(begin);
	}
	return (0);
}
