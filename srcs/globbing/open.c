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


char	ft_is_wildcard(char	*buff)
{
	if (!ft_strcmp(buff, "**"))
		return (2);
	if (ft_strchr(buff, '*') || (ft_strchr(buff, '[') && ft_strchr(buff, ']')) ||
			ft_strchr(buff, '?'))
		return (1);
	return (0);
}


char	*ft_set_recu_path(char *path, char *file, int index)
{
	char	*recu_path;
	int		size;

	size = ft_strlen(path) + ft_strlen(file) + 1;
	recu_path = ft_strnew(size);
	ft_strncpy(recu_path, path, index);
	ft_strcat(recu_path, file);
	recu_path[index + ft_strlen(file)] = '/';
	ft_strcat(recu_path, &path[index]);
	return (recu_path);

}

char	*ft_set_new_path(char *path, char *file, int index, int size)
{
	char	*new_path;

	new_path = ft_strnew(ft_strlen(path) + ft_strlen(file) - size + 1);
	ft_strncpy(new_path, path, index);
	ft_strcat(new_path, file);
	ft_strcat(new_path, &path[index + size]);
	return(new_path);
}

void	ft_get_glob(DIR *dir, char *path, char *glob, t_list **begin)
{
	char			buff[256];
	struct dirent	*file;
	int				end;
	int				ret;

	printf("A l'ouverture le buff vaut %s et glob %s\n", path, glob);
	end = ft_strlen(ft_strcpy(buff, path));
	if (!*glob)
		ft_list_push_back(begin, ft_lstnew(ft_strdup(buff), 0));
	if (!dir)
		return;
	if (*glob == '/')
	{
		printf("Ajout du /\n");
		ft_get_glob(dir, ft_strcat(buff, "/"), ++glob, begin);
	}
	else
	{
		while ((file = readdir(dir)))
		{
			printf("Le fichier %s a été lu pour glob: %s\n", file->d_name, glob);
			if (!ft_strcmp(file->d_name, ".") && !ft_strncmp(glob, "**/", 3))
			{
				printf("Envoi de la fonction récursive sur %s avec glob %s\n", buff, glob + ft_strlencc(glob, '/'));
				if (!*buff)
					if (glob[3])
						ft_get_glob(opendir("."), buff, (glob + 1 + ft_strlencc(glob, '/')), begin);
					else
						ft_get_glob(opendir("."), buff, glob, begin);
				else
					if (glob[3])
						ft_get_glob(opendir(buff), buff, (glob + 1 + ft_strlencc(glob, '/')), begin);
					else
						ft_get_glob(opendir(buff), buff, glob, begin);
				ft_bzero(&buff[end], 255 - end);
			}

			if (is_valid(0, 0, glob, file->d_name) && ((ft_strcmp(file->d_name, ".")
							&& ft_strcmp(file->d_name, "..") && (*(file->d_name) != '.' ||
								(*(file->d_name) == '.' && is_valid(0, 0, ".*", glob))))
						|| (is_valid(0, 0, ".", glob) && !ft_strcmp(file->d_name, "."))
						||(is_valid(0, 0, "..", glob) && !ft_strcmp(file->d_name, ".."))))
			{
				ft_strcat(buff, file->d_name);
				if (ft_strncmp(glob, "**/", 3))
				{
					printf("Valide, fction relancée sur buff: %s glob: %s\n", buff, glob + ft_strlencc(glob, '/'));
					ft_get_glob(opendir(buff), buff, (glob + ft_strlencc(glob, '/')), begin);
				}
				else
				{
					printf("Lancement de la fonction récursive\n");
					ft_get_glob(opendir(buff), ft_strcat(buff, "/"), glob, begin);
				}
				ft_bzero(&buff[end], (255 - end));
			}
			printf("ret: %d\n", ret);
		}
	}
}

int		main(int ac, char **av)
{
	DIR		*stream;
	int		size;
	t_list	*begin;
	char	buff[256];

	ft_bzero(buff, 256);
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
		ft_get_glob(stream, buff, av[1],  &begin);
		ft_print_list(begin);
	}
	return (0);
}

/*
   int	main(void)
   {
   char test[] = "coco";
   char	glob[] = "*.";

   if ((is_valid(0, 0, glob, test)))
   printf("OK\n");
   return (0);
   }
   */
/*
//test de ft_set_recu_path
int		main(int ac, char **av)
{
char	*path;

if (ac > 3)
{
path = ft_set_recu_path(av[1], av[2], atoi(av[3]));
printf("%s\n", path);
}
return (0);


}*/
