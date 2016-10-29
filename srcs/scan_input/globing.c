/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:39:26 by maxpetit          #+#    #+#             */
/*   Updated: 2016/10/29 13:24:29 by maxpetit         ###   ########.fr       */
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

static int ft_opendir(t_stream *stream, t_list **list, char *path, char *needle)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*tmp;
	char			*str;

	tmp = NULL;
	if (!(dir = opendir(path)))
		return (1);
	while ((file = readdir(dir)))
	{
		str = ft_strjoin(path, file->d_name);
		str = ft_strjoin(str, "/");
		if ((ft_strstri(file->d_name, needle) != -1
			|| !ft_check_c(needle)) && file->d_name[0] != '.')
		{
			if (!(tmp = ft_lstnew((void *)str, sizeof(str))))
				return (1);
			ft_list_push_back(list, tmp);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

static int	ft_fillist(t_stream *stream, t_list *list, t_globing *glob, char *needle)
{
	struct stat	statmp;
	t_list		*tmp;

	while (list)
	{
		if (!(tmp = ft_lstnew(list->data, sizeof(list->data))))
			return (1);
		ft_list_push_back(&glob->lstmp, tmp);
		if (stat(tmp->data, &statmp) != -1)
			if (S_ISDIR(statmp.st_mode) && glob->mode > 1)
				ft_checkdir(stream, NULL, glob, list->data, needle);
		list = list->next;
	}
	return (0);
}

int		ft_checkdir(t_stream *stream, t_list *list, t_globing *glob, char *path, char *needle)
{
	if (!ft_opendir(stream, &list, path, needle) && !ft_fillist(stream, list, glob, needle))
		return (1);
	return (0);
}

static char *ft_get_partpath(char *path)
{
	int		i;
	char	*new;

	i = 0;
	while (path[i] && path[i] != '/')
		i++;
	if (!i)
		return (NULL);
	new = ft_strnew(i);
	new = ft_strncpy(new, path, i);
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

static char *ft_get_needle(char *str)
{
	int		i;
	char	*new;
	char	tmp[2];

	i = -1;
	new = NULL;
	while (str[++i])
	{
		if (str[i] != '*')
		{
			tmp[0] = str[i];
			tmp[1] = 0;
			if (!new)
				new = ft_strdup(tmp);
			else
				new = ft_strjoin(new, tmp);
		}
	}
	return (new);
}

char	*ft_printlst(t_stream *stream, t_list *list)
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
		tmp = tmp->next;
	}
	return (str);
}

static char *ft_strndup(char *src, int len)
{
	char *new;

	new = ft_strnew(len);
	new = ft_strncpy(new, src, len);
	return (new);
}

static void ft_launch_checkdir(t_stream *stream, t_globing *glob, char *part)
{
	int		len;
	char	*needle;
	char	*new;
	t_list	*list;

	needle = NULL;
	list = NULL;
	glob->mode = ft_get_mode(glob);
	needle = ft_get_needle(part);
	needle = (!needle) ? ft_strdup("*") : needle;
	new = ft_strndup(glob->path, ft_strlen(glob->path) - ft_strlen(part));
	if (!ft_checkdir(stream, NULL, glob, new, needle))
	{
		len = ft_list_size(glob->lstmp);
		while (len-- > 0)
		{
			ft_checkdir(stream, list, glob, glob->lstmp->data, needle);
			glob->lstmp = glob->lstmp->next;
		}
	}
	ft_strdel(&needle);
	ft_strdel(&new);
}

void	ft_test(char *str, t_stream *stream)
{
	int i;

	ft_putmess(stream, str);
	ft_goend(stream);
}

void ft_loop_path(t_stream *stream, t_globing *data)
{
	int		i;
	size_t	len;
	char	*part;
	char	*str;

	i = 0;
	data->ret = -1;
	data->mode = 0;
	data->lstmp = NULL;
	data->lstprint = NULL;
	part = NULL;
	len = ft_strlen(data->path);
	while (data->path[i] && data->path[i] == '/')
		i++;
	while ((size_t)i <= len && (part = ft_get_partpath(&(data)->path[i])))
	{
		i += ft_strlen(part);
		data->path[i] = 0;
		data->ret = ft_search_chr(part, '*');
		ft_launch_checkdir(stream, data, part);
		data->path[i] = ((size_t)i != len) ? '/' : 0;
		ft_strdel(&part);
		i++;
	}
	str = ft_printlst(stream, data->lstmp);
	ft_test(str, stream);
//	ft_underline_mess(str, stream);
}
