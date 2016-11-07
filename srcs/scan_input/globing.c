/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:39:26 by maxpetit          #+#    #+#             */
/*   Updated: 2016/11/07 12:03:30 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_c(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != '*')
			return (1);
	return (0);
}

int ft_search_chr(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c && str[i + 1] && str[i + 1] == c)
			return (-2);
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int		ft_match_n_match(char *str, char *needle)
{
	if (!*needle || !*str)
		return ((!*needle && !*str) ? 1 : 0);
	if (*needle != '*')
		return ((*needle == *str) ? ft_match_n_match(str + 1, needle + 1) : 0);
	return (ft_match_n_match(str, needle + 1) ? 1 : ft_match_n_match (str + 1, needle));
}

static int ft_opendir(t_stream *stream, t_list **list, char *path, char *needle)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*tmp;
	char			*str;
	int				ret;
	char			print[2];

	tmp = NULL;
	if (!(dir = opendir(path)))
		return (1);
	while ((file = readdir(dir)))
	{
		ret = ft_match_n_match(file->d_name, needle);
		print[0] = ret + '0';
		print[1] = 0;
		ft_underline_mess(print, stream);
	/*	if (!ft_strcmp(path, ".") && file->d_name[0] != '.')
		{
			str = ft_strnew(ft_strlen(file->d_name) + 1);
			str = ft_strcat(file->d_name, "/");
		}
		else if (ft_match_n_match(file->d_name, needle) && file->d_name[0] != '.')
		{
			str = ft_strnew(ft_strlen(path) + ft_strlen(file->d_name) + 1);
			str = ft_strcat(path, file->d_name);
			str = ft_strcat(str, "/");
		}
		if (str)
		{
			if (!(tmp = ft_lstnew((void *)str, 1)))
				return (1);
			ft_list_push_back(list, tmp);
		//	free(str);
		}*/
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}
/*
**Remplie la list en inserant, si deux etoiles ont ete trouve dans le path,  
**a la suite de chaque repertoire trouve les sous dossiers et sous repertoire
**correspondant
*/
static int	ft_fillist(t_stream *stream, t_list *list, t_globing *glob, char *needle)
{
	struct stat	statmp;
	t_list		*tmp;

	while (list)
	{
		if (!(tmp = ft_lstnew(list->data, 1)))
			return (1);
		if (stat(tmp->data, &statmp) != -1)
			if (S_ISDIR(statmp.st_mode) && glob->mode > 1)
				ft_checkdir(stream, NULL, glob, list->data, needle);
		ft_list_push_back(&glob->lstmp, tmp);
		list = list->next;
	}
	return (0);
}

int		ft_checkdir(t_stream *stream, t_list *list, t_globing *glob, char *path, char *needle)
{
//	dprintf(stream->fd, "WAZA");
//	if (ft_strstri(glob->path, "*") == -1)
//		return (1);
	if (!ft_opendir(stream, &list, path, needle) && !ft_fillist(stream, list, glob, needle))
		return (1);
	return (0);
}
/*
**Renvoie une chaine de charactere malloc, allant jusqu'a la premiere occurence
**de c
*/
static char *ft_inv_strchr(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	new = ft_strnew(i);
	new = ft_strncpy(new, str, i);
	return (new);
}

static int ft_get_mode(t_globing *data)
{
	int new;

	if (data->ret == -1)
		new = 0;
	if (data->ret >= 0 && data->mode <= 1)
		new = 1;
	if (data->ret == -2)
		new = 2;
	if (data->ret >= 0 && data->mode > 1)
		new = 3;
	return (new);
}
/*
**Concatene dans une chaine chaque path stocke dans chaque maillon de list
*/
char	*ft_printlst(t_stream *stream, t_globing *glob, t_list *list)
{
	int		i;
	char	*str;
	t_list	*tmp;

	i = 0;
	str = NULL;
	tmp = list;
	while (list)
	{
		i += ft_strlen(((char *)list->data));
		list = list->next;
	}
	str = ft_strnew(i);
	while (tmp)
	{
		str = ft_strcat(str, ((char *)tmp->data));
		str[ft_strlen(str) - 1] = ' ';
		tmp = tmp->next;
	}
	return (str);
}

static char *ft_strndup(char *src, int len)
{
	char *new;

	if (!len)
		return (NULL);
	new = ft_strnew(len);
	new = ft_strncpy(new, src, len);
	return (new);
}
/*
**Affectation de dir avec la valeur du path sans le dernier repertoire renvoye
**par ft_loop_path, par contre si ce dernier repertoire est egal a un ou plusieurs
** '*' alors dir est egual a '.'. Si dir comprend une ou plusieurs '*'
**alors ft_checkdir est envoye avec comme arguments successivement chaque path 
**enregistre dans la list de glob
*/
static void ft_launch_checkdir(t_stream *stream, t_globing *glob, char *part)
{
	int		len;
	char	*dir;
	char	tmp[2];
	t_list	*list;

	list = NULL;
	glob->mode = ft_get_mode(glob);
	dir = ft_strndup(glob->path, ft_strlen(glob->path) - ft_strlen(part));
	if (!ft_check_c(glob->path))
		dir = ft_strdup(".");
//	ft_underline_mess(part, stream);
	if (!ft_checkdir(stream, NULL, glob, dir, part))
	{
		len = ft_list_size(glob->lstmp);
		while (len-- > 0)
		{
			ft_checkdir(stream, list, glob, glob->lstmp->data, part);
			glob->lstmp = glob->lstmp->next;
		}
	}
	ft_strdel(&dir);
}
/*
**Insere au sein du path sur lequel etait positionne le curseur, le/les nouveau(x)
**path apres le globing
*/
static void		ft_gappend(t_stream *stream, t_globing *data, char *str)
{
	size_t				pos;
	size_t				len;
	char				*kill;

	len = ft_strlen(str);
	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + len))
			&& (stream->state = -2) && ft_freegiveone((void **)&kill))
			return ;
		ft_strncpy(stream->command, kill, pos);
		ft_strcpy(stream->command + pos, str);
		ft_strcpy(stream->command + pos + len, kill + data->end);
		ft_freegiveone((void **)&kill);
	}
	else if (!(stream->command = ft_strdup(str)))
		stream->state = -2;
	ft_push_history(stream, stream->config);
	ft_gohome(stream);
	ft_flush(stream);
	while (len--)
		ft_mvright(stream);
}
/*
**Permet de parcourir le path repertoire par repertoire et de printer 
**finalement le resultat apres le globing
*/
void ft_loop_path(t_stream *stream, t_globing *glob)
{
	int		i;
	size_t	len;
	char	*part;

	i = 0;
	part = NULL;
	len = ft_strlen(glob->path);
	glob->ret = -1;
	while (glob->path[i] && glob->path[i] == '/')
		i++;
	while ((size_t)i <= len && (part = ft_inv_strchr(&(glob)->path[i], '/')))
	{
		i += ft_strlen(part);
		glob->path[i] = 0;
		glob->ret = ft_search_chr(part, '*');
		ft_launch_checkdir(stream, glob, part);
		glob->path[i] = ((size_t)i != len) ? '/' : 0;
		ft_strdel(&part);
		i++;
	}
	part = ft_printlst(stream, glob, glob->lstmp);
	ft_gappend(stream, glob, part);
//	ft_freelist(glob->lstmp);
	ft_strdel(&part);
}
