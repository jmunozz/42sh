/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:39:26 by maxpetit          #+#    #+#             */
/*   Updated: 2016/10/28 15:27:25 by maxpetit         ###   ########.fr       */
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

static int ft_search_chr(char *str, char c)
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

static int ft_opendir(t_globing *data, char *path, char *needle)
{
	DIR			*dir;
	struct dirent	*file;
	t_list		*tmp;
	char		*str;

	elem = NULL;
	if (!(dir = opendir(path)))
		return (1);
	while ((file = readdir(dir)))
	{
		str = ft_strjoin(path, "/");
		str = ft_strjoin(str, file->d_name);
		if (ft_strstri(file->d_name, needle) != -1 || !ft_check_c(needle))
		{
			if (!(elem = ft_lstnew((void *)str, sizeof(str))))
				return (1);
			ft_list_push_back(&(data)->lstprint, elem);
		}
		if (data->mode > 1)
		{
			if (!(elem = ft_lstnew((void *)str, sizeof(str))))
				return (1);
			ft_list_push_back(&(data)->lstmp, elem);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

static void ft_checkdir(t_stream *stream, t_globing *data, char *path, char *needle)
{
	struct stat	statmp;

	ft_underline_mess("WAOU", stream);
	if (ft_opendir(data, path, needle))
		while (data->lstmp)
		{
			if (stat(data->lstmp->data, &statmp) != -1)
				if (S_ISDIR(statmp.st_mode) && (data->mode > 1))
					ft_checkdir(stream, data, data->lstmp->data, needle);
			data->lstmp = data->lstmp->next;
		}
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

	new = (data->ret == -1) ? 0 : data->mode;
	new = (data->ret >= 0 && data->mode <= 1) ? 1 : data->mode;
	new = (data->ret == -2) ? 2 : data->mode;
	new = (data->ret >= 0 && data->mode > 1) ? 3 : data->mode;
	return (new);
}

static char *ft_get_needle(char *str)
{
	int		i;
	char	*new;
	char	*cpy;

	i = -1;
	new = NULL;
	while (str[++i])
	{
		if (str[i] != '*')
		{
			if (new)
			{
				cpy = new;
				new = ft_strjoin(new, &str[i]);
				ft_strdel(&cpy);
			}
		}
	}
	return (new);
}

static void ft_launch_checkdir(t_stream *stream, t_globing *data, char *part)
{
	char *needle;

	needle = NULL;
	data->mode = ft_get_mode(data);
	if (data->ret != -1)
	{
		needle = ft_get_needle(part);
		ft_checkdir(stream, data, part, needle);
	}
	if (needle)
		ft_strdel(&needle);
}

void ft_loop_path(t_stream *stream, t_globing *data)
{
	int		i;
	char	*part;

	i = 0;
	data->ret = -1;
	data->mode = 0;
	part = NULL;
	while ((part = ft_get_partpath(&(data)->path[i])))
	{
		data->path[ft_strlen(part)] = 0;
		ft_launch_checkdir(stream, data, part);
		data->ret = ft_search_chr(part, '*');
		data->path[ft_strlen(part)] = '/';
		i += ft_strlen(part) + 1;
		ft_strdel(&part);
	}
	if (part)
	{
		ft_launch_checkdir(stream, data, part);
		ft_strdel(&part);
	}
}
