/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2016/10/19 18:41:51 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
   static int		ft_test_access(char *path, char *cpy)
   {
   int			i;
   struct stat	stat_file;

   i = 0;
   if (-1 == access(cpy, F_OK) && ++i)
   ft_putstr_str_fd("21sh: directory doesn't exist: ", path, "\n", 2);
   else if (-1 == stat(cpy, &stat_file) && ++i)
   ft_putstr_str_fd("21sh: stat failed on: ", path, "\n", 2);
   else if (!S_ISDIR(stat_file.st_mode) && ++i)
   ft_putstr_str_fd("21sh: ", path, ": not a directory\n", 2);
   else if (-1 == access(cpy, X_OK) && ++i)
   ft_putstr_str_fd("21sh: permission denied: ", path, "\n", 2);
   return (i);
   }*/

static int ft_search_chr(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	if ((size_t)i == ft_strlen(str))
		i = -1;
	return (i);
}

static void ft_loop_path(t_stream *stream, char *path)
{
	int		i;
	char	*tmp;
	char	*cpy;

	i = ft_search_chr(path, '/');
	tmp = ft_strnew(i);
	tmp = ft_strncpy(tmp, path, i);
	//	ft_open_file(stream, cpy);
	ft_underline_mess(tmp, stream);
	cpy = ft_strdup(path);
	tmp = cpy;
	while ((tmp = ft_strchr(tmp + 1, '/')))
	{
		*tmp = 0;
		//		ft_open_file(stream, cpy);
		//		ft_underline_mess(cpy, stream);
		*tmp = '/';
	}
	ft_strdel(&cpy);
}

static int ft_check_marge(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' || c == ';')
		return (1);
	return (0);
}

static char *ft_get_current_command(t_stream *stream, int *new_pos)
{
	char	*cmd;
	int		i;
	int		begin;
	int		len;

	i = stream->pos;
	len = 0;
	while (i >= 0 && (!ft_check_marge(stream->command[i])) && ++len)
		i--;
	i = (i == -1) ? 0 : i;
	i = (ft_check_marge(stream->command[i]) && len) ? i + 1 : i;
	begin = i++;
	len = 0;
	while (stream->command[i] && (!ft_check_marge(stream->command[i])) && ++len)
		i++;
	cmd = ft_strnew(++len);
	cmd = ft_strncpy(cmd, &stream->command[begin], len);
	*new_pos = stream->pos - begin;
	return (cmd);
}

static int ft_globing_curent_file(/*t_stream *stream,*/ char *str, int new_pos)
{
	int i;

	i = 0;
	if (str[new_pos] == '*')
	{
		i = 1;
		if (new_pos > 0)
			i = (str[new_pos - 1] == ' ') ? i : 0;
		if (str[new_pos + 1] && i == 1)
			i = (str[new_pos + 1] == ' ') ? i : 0;
	}
	else if (new_pos > 0 && str[new_pos - 1] == '*')
	{
		i = 1;
		if (new_pos > 1)
			i = (str[new_pos - 2] == ' ') ? i : 0;
		if (i == 1 && str[new_pos])
			i = (str[new_pos] == ' ') ? i : 0;
	}
	return (i);
}

static int ft_globing_path_file(/*t_stream *stream,*/ char *str, int new_pos, char *path)
{
	int		begin;
	int		i;

	i = 0;
	if (str[new_pos] != ' ' || (new_pos > 0 && str[new_pos] == ' ' && str[new_pos - 1] == '*' && ++i))
	{
		new_pos =  (i) ? new_pos - 1 : new_pos ;
		while (new_pos > 0 && str[new_pos] != ' ')
			new_pos--;
		new_pos = ((new_pos != -1) && (str[new_pos] == ' ')) ? new_pos + 1 : new_pos;
		new_pos = (new_pos == -1) ? 0 : new_pos;
		begin = new_pos;
		i = 0;
		while (str[new_pos] && str[new_pos] != ' ' && ++i)
			new_pos++;
		path = ft_strnew(i);
		path = ft_strncpy(path, &str[begin], i);
		if (ft_search_chr(path, '*') != -1)
			return (1);
	}
	return (0);
}

static void ft_open_dir(t_stream *stream, char *filename)
{
	opendir(filename);
}

static int ft_ifglobing(/*t_stream *stream,*/ char *str, int new_pos)
{
	if (ft_search_chr(str, '*') == -1)
		return (-1);
	if (ft_globing_curent_file(/*stream,*/ str, new_pos) == 1)
		return (2);
	if (ft_globing_path_file(/*stream,*/ str, new_pos, path) == 1)
		return (1);
	return (-1);
}

void	ft_autocomp(t_stream *stream)
{
	int		ret;
	int		new_pos;
	char	*cmd;
	char	*path;

	new_pos = 0;
	ft_bzero(stream->buf, 4);
	cmd = ft_get_current_command(stream, &new_pos);
	path = NULL;
	if ((ret = ft_ifglobing(/*stream,*/ cmd,  new_pos, path)) != -1)
	{
		if (ret == 1)
			ft_loop_path(stream, path);
		else if (ret == 2)
			ft_open_dir(stream, ".");
	}
//	else
//		ft_underline_mess("NO", stream);
	ft_strdel(&cmd);
}
