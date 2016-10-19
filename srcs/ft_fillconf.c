/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillconf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 10:25:02 by rbaran            #+#    #+#             */
/*   Updated: 2016/05/25 15:40:52 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>
#include <stdio.h>

static t_bin	*ft_addbin(char *name, char *path)
{
	t_bin	*bin;

	if ((bin = (t_bin*)ft_memalloc(sizeof(t_bin))))
	{
		bin->name = ft_strdup(name);
		if (path[ft_strlen(path)] != '/')
			bin->path = ft_strjoin(path, "/");
		else
			bin->path = ft_strdup(path);
		bin->next = NULL;
	}
	return (bin);
}

static t_bin	*ft_sortedinsert(char *name, char *path, t_bin *bin)
{
	t_bin	*bin_begin;
	t_bin	*bin_buff;

	bin_begin = bin;
	if (ft_strcmp(bin->name, name) > 0)
	{
		bin = ft_addbin(name, path);
		bin->next = bin_begin;
	}
	else
	{
		bin_buff = bin_begin;
		bin_begin = bin_begin->next;
		while (bin_begin && ft_strcmp(bin_begin->name, name) <= 0)
		{
			bin_buff = bin_begin;
			bin_begin = bin_begin->next;
		}
		bin_buff->next = ft_addbin(name, path);
		bin_buff->next->next = bin_begin;
	}
	return (bin);
}

static t_bin	*ft_fillconfbins(DIR *directory, char *path, t_bin *bin)
{
	t_dirent		*readfile;

	while ((readfile = readdir(directory)) != NULL)
		if (ft_strcmp(readfile->d_name, ".") &&
				ft_strcmp(readfile->d_name, ".."))
		{
			if (!bin)
				bin = ft_addbin((char*)readfile->d_name, path);
			else
				bin = ft_sortedinsert((char*)readfile->d_name, path, bin);
		}
	return (bin);
}

static t_bin	*ft_readconfpaths(char **paths_bin)
{
	DIR			*directory;
	struct stat	stats;
	t_bin		*bin;

	bin = NULL;
	while (paths_bin && *paths_bin)
	{
		if (!(stat(*paths_bin, &stats)))
			if ((directory = opendir(*paths_bin)))
			{
				bin = ft_fillconfbins(directory, *paths_bin, bin);
				closedir(directory);
			}
		paths_bin++;
	}
	return (bin);
}

t_conf			*ft_fillconf(char **env)
{
	char	**split;
	char	**split_path_bins;
	t_conf	*config;

	if (!(config = ft_memalloc(sizeof(t_conf))))
		return (NULL);
	config->env = ft_fillenv(env, ft_splitsize(env));
	if ((split = ft_parseenv(config->env, "PATH")))
	{
		if ((split_path_bins = ft_strsplit(split[1], ':')))
		{
			config->bin = ft_readconfpaths(split_path_bins);
			ft_free_split(split_path_bins);
			free(split_path_bins);
		}
		ft_free_split(split);
		free(split);
	}
	if ((split = ft_parseenv(config->env, "TERM")))
	{
		config->term = tgetent(NULL, *(split + 1));
		ft_free_split(split);
		free(split);
	}
	return (config);
}
