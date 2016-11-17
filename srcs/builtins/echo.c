/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:33:52 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/17 18:40:16 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:srcs/scan_input/autocomp.c
static int ft_check_marge(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' || c == ';'|| c == ' ')
		return (1);
	return (0);
}

static char *ft_get_path(t_stream *stream, t_globing *data)
{
	int		i;
	int		j;
	int		len;
	char	*path;

	i = stream->pos;
	len = 0;
	while (i >= 0 && (!ft_check_marge(stream->command[i])))
		i--;
	j = ++i;
	while (stream->command[i] && (!ft_check_marge(stream->command[i])) && ++len)
		i++;
	data->end = i;
	path = ft_strnew(len);
	path = ft_strncpy(path, &(stream)->command[j], len);
	stream->pos = j;
	if ((ft_strstri(path, "*")) != -1)
		return (path);
	return (NULL);
}

void	ft_autocomp(t_stream *stream)
{
	t_globing	glob;
	int			end;

	ft_bzero(stream->buf, 4);
	ft_bzero(&glob, sizeof(void*));
	if ((glob.path = ft_get_path(stream, &glob)))
		ft_loop_path(stream, &glob);
	else
		ft_underline_mess("NO", stream);
	ft_strdel(&glob.path);
=======
static int	ft_parseparams(char **argv, int *param)
{
	int	i;

	i = 0;
	while (argv[++i] && argv[i][0] == '-' && argv[i][1] == 'n')
		*param |= ECHO_N;
	return (i);
}

void	ft_echo(char **argv)
{
	int	i;
	int	param;

	param = 0;
	i = ft_parseparams(argv, &param);
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[++i])
			ft_putchar(' ');
	}
	if (!(param & ECHO_N))
		ft_putchar('\n');
>>>>>>> tboos/master:srcs/builtins/echo.c
}
