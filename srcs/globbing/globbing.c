/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:09:33 by jmunoz            #+#    #+#             */
/*   Updated: 2016/11/25 21:18:57 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globbing.h"

/*
** Save once and  return list with valid files pathnames.
*/

static t_list	**ft_save_list(t_list **begin)
{
	static t_list **save = NULL;

	if (!save)
		save = begin;
	return (save);
}

/*
** For one directory, check if each file fill the glob, append it to the saved
** path if ok. Discard "." and ".." and hidden files if not explicitely
** mentionned in glob. Call ft_glob with next path section in glob.
*/

static void		ft_check_file(char *file, char *glob, char *buf, int end)
{
	if (!ft_strcmp(file, ".") && !ft_strncmp(glob, "**/", 3))
	{
		if (glob[3])
			ft_glob(opendir((!*buf) ? "." : buf), buf,
			(glob + ft_strlenc(glob, '/') + 1));
		else
			ft_glob(opendir((!*buf) ? "." : buf), buf, (glob + 1));
	}
	if (ft_match(glob, file) && ((ft_strcmp(file, ".") && ft_strcmp(file, "..")
	&& (*(file) != '.' || ft_match(".*", glob))) || (ft_match(".", glob) &&
	!ft_strcmp(file, ".")) || (ft_match("..", glob) && !ft_strcmp(file, ".."))))
	{
		if (ft_strcat(buf, file) && ft_strncmp(glob, "**/", 3))
			ft_glob(opendir(buf), buf, (glob + ft_strlenc(glob, '/')));
		else
			ft_glob(opendir(buf), ft_strcat(buf, "/"), glob);
		ft_bzero(&buf[end], (255 - end));
	}
}

/*
** Recursive function. If glob comes at a end, add the pathname to the list.
** if *glob is /, append it to the pathname and restart function. If it comes to
** a valid path section in glob, check the files that might be valid.
*/

void			ft_glob(DIR *dir, char *path, char *glob)
{
	char			buf[256];
	struct dirent	*file;
	int				end;
	t_list			**begin;

	begin = ft_save_list(NULL);
	end = ft_strlen(ft_strcpy(buf, path));
	if (!*glob)
		ft_list_push_back(begin, ft_lstnew(ft_strdup(buf), 0));
	if (dir && *glob == '/')
		ft_glob(dir, ft_strcat(buf, "/"), ++glob);
	else if (dir)
		while ((file = readdir(dir)))
			ft_check_file(file->d_name, glob, buf, end);
}

/*
** debug.
*/

void			ft_print_list(t_list *begin)
{
	printf("--Impression de la liste--\n");
	while (begin)
	{
		printf("%s %zu\n", begin->data, begin->data_size);
		begin = begin->next;
	}
}

/*
** Main a retravailler avant integration dans le 42sh.
*/

int				main(int ac, char **av)
{
	DIR		*stream;
	int		size;
	t_list	*begin;
	char	buf[256];

	ft_bzero(buf, 256);
	begin = NULL;
	ft_save_list(&begin);
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
		ft_glob(stream, buf, av[1]);
		ft_print_list(begin);
	}
	return (0);
}
