#include "../../includes/autocomp.h"

/*static	void	debug(char *str, char *str2, int nb)
{
	ft_putendl(str);
	ft_putendl(str2);
	ft_putnbr(nb);
	ft_putchar('\n');
}*/

static void		do_list(t_stream *stream, struct dirent *file)
{
	size_t data_size;

	data_size = 0;
	if (file->d_name[0] == '.')
	{
		if (COMP_BEGIN[0] == '.' && ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
		{
			if (!COMP_BEGIN_LIST)
				COMP_BEGIN_LIST = ft_lstnew(ft_strdup(file->d_name), data_size);
			else
				ft_list_push_back(&(COMP_BEGIN_LIST), ft_lstnew(ft_strdup(file->d_name), data_size));
			get_pad(stream, file->d_name);
		}
	}
	else
	{
		if (!COMP_BEGIN_LIST)
			COMP_BEGIN_LIST = ft_lstnew(ft_strdup(file->d_name), data_size);
		else
			ft_list_push_back(&(COMP_BEGIN_LIST), ft_lstnew(ft_strdup(file->d_name), data_size));
		get_pad(stream, file->d_name);
	}
}
/*
** Fonction qui set la chaîne de caractère à comparer aux fichiers du dossier
** ouvert. Cette chaîne est 1. NULLE, 2.équivalente à la commande passée,
** 3. équivalente au dernier élément du path entré en commande.
*/
void			set_comp(char *str, char **comp, size_t *len_comp, int mode, t_stream *stream)
{
	if (!mode || mode == 1)
		*comp = NULL;
	else if (!(*comp = ft_strrchr(str, '/')))
		*comp = str;
	else
	{
		(*comp)++;
		ft_freegiveone((void**)&COMP_BEGIN);
		COMP_BEGIN = ft_strdup(*comp);
	}
	*len_comp = (!mode || mode == 1) ? 0 : ft_strlen(*comp);
}
/*
** Appelle set_comp, puis set up le dossier à parcourir. Plusieurs cas de figure
** 1. PATH, 2. Dossier courant, 3. Dossier mentionne dans la commande.
*/
char		**set_dir(char *str, int mode,
			t_stream *stream, char **comp, size_t *len_comp)
{
	char	**dir;
	char	*tmp;
	char	*path;

	path = ft_strdup(str);
	set_comp(str, comp, len_comp, mode, stream);
	if (mode % 2)
		dir = ft_getenvtab("PATH", stream->config->env);
	else
	{
		if (!mode || mode == 1)
			tmp = getcwd(NULL, 0);
		else if (ft_strlen(path) == *len_comp)
			tmp = getcwd(NULL, 0);
		else
			tmp = ft_strsub(path, 0, (ft_strlen(path) - *len_comp));
		dir = ft_strsplit(tmp, ' ');
		free(tmp);
	}
	ft_freegiveone((void**)&path);
	return (dir);
}
/*
** Appelle set_dir. Construit la liste en fonction du ou des dossiers ouverts
** (**dir) et de la chaîne à comparer (*comp). free **dir (à rectifier)
*/
void		build_list(char *str, int mode, t_stream *stream)
{
	DIR				*directory;
	struct dirent	*file;
	size_t			len_comp;
	char			**dir;
	char			*comp;
	int				i;


	i = -1;
	dir = set_dir(str, mode, stream, &comp, &len_comp);
	while (dir[++i])
	{
		if ((directory = opendir(dir[i])))
		{
			while ((file = readdir(directory)))
			{
				if (!comp || !*comp)
					do_list(stream, file);
				else if (!ft_strncmp(comp, file->d_name, len_comp))
					do_list(stream, file);
			}
			closedir(directory);
		}
		free(dir[i]);
		dir[i] = NULL;
	}
	get_size_list(stream);
	free(dir);
}

