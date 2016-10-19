/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:22:50 by rbaran            #+#    #+#             */
/*   Updated: 2016/04/13 15:20:15 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 1024

typedef struct	s_fd
{
	int			fd;
	char		*line;
	char		*begin_line;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(int const fd, char **line);

#endif
