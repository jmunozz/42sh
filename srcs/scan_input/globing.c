/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:39:26 by maxpetit          #+#    #+#             */
/*   Updated: 2016/11/02 17:33:03 by maxpetit         ###   ########.fr       */
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
		return (!*needle && !*str ? 1 : 0);
	if (*needle != '*')
		return (*needle == *str ? ft_match_n_match(str + 1, needle + 1) : 0);
	return (ft_match_n_match(str, needle + 1) ? 1 : ft_match_n_match (str + 1, needle));
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
		if (ft_match_n_match(file->d_name, needle) && file->d_name[0] != '.')
		{
			if (!(tmp = ft_lstnew((void *)str, 1)))
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
	if (ft_strstri(glob->path, "*") == -1)
		return (1);
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
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = NULL;
	while (str[++i])
		if (str[i] != '*')
			j++;
	i = -1;
	new = ft_strnew(j);
	while (str[++i])
		if (str[i] != '*')
			new = ft_strcat(new, str[i]);
	return (new);
}

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

static void	ft_initialize(t_globing *glob)
{
	glob->ret = -1;
	glob->mode = 0;
	glob->print = 0;
	glob->lstmp = NULL;
	glob->lstprint = NULL;
}

void ft_loop_path(t_stream *stream, t_globing *glob)
{
	int		i;
	size_t	len;
	char	*part;

	i = 0;
	part = NULL;
	len = ft_strlen(glob->path);
	ft_initialize(glob);
	while (glob->path[i] && glob->path[i] == '/')
		i++;
	while ((size_t)i <= len && (part = ft_get_partpath(&(glob)->path[i])))
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
	ft_freelist(glob->lstmp);
	ft_strdel(&part);
}
