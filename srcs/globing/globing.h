/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:26:49 by maxpetit          #+#    #+#             */
/*   Updated: 2016/10/17 17:00:37 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

typedef struct	s_glob
{
		char	*needle;
		int		recursive;
}				t_glob;

void	ft_star(char *str);
void	ft_parser(char *str);

#endif
