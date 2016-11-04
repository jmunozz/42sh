/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:27:28 by tboos             #+#    #+#             */
/*   Updated: 2016/09/21 17:04:55 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_gomatch(t_stream *stream, unsigned int go,
							void (*mv)(t_stream *))
{
	while (stream->pos != go) //Tant que la position du curseur est différente de go.
		mv(stream); //On applique la fonction (mvright ou mvleft) passée en param.
}

int				ft_putcharint(int i)
{
	char			c;

	c = i;
	ft_putchar(c);
	return (c);
}

void			ft_tputs(t_stream *stream)
{
	if (stream->config->term_state)
		tputs(tgetstr(stream->tput, NULL), stream->fd, &ft_putcharint);
	else if (stream->tput[0] == 'u')
		ft_putstr_fd(TUP, stream->fd);
	else if (stream->tput[0] == 'l')
		ft_putstr_fd(TLE, stream->fd);
	else if (stream->tput[0] == 'n')
		ft_putstr_fd(TND, stream->fd);
	else if (stream->tput[0] == 'c')
		ft_putstr_fd(TCD, stream->fd);
	else if (stream->tput[0] == 'd' && stream->tput[1] == 'o')
		ft_putstr_fd(TDO, stream->fd);
	else
		ft_putstr_fd(TDL, stream->fd);
}

void			ft_mvleft(t_stream *stream)
{
	unsigned int	i;

	i = 0;
	if (stream->pos) // on s'assure qu'on ne bute pas contre le prompt.
	{
		//Si on est pas avant un \n ni sur le premier élement d'une ligne
		if (stream->command[stream->pos - 1] != '\n'
			&& (stream->config->prompt_len + stream->pos) % stream->col)
		{
			stream->tput = "le";
			ft_tputs(stream); //on recule le curseur d'un pas a gauche.
		}
		else
		{
			stream->tput = "nd";
			while (++i <= stream->col)
				ft_tputs(stream); //on va en bout de ligne
			stream->tput = "up"; //on saute un ligne.
			ft_tputs(stream);
		}
		stream->pos--; //on actualise la position du curseur de commande.
		if (i)
			ft_checknewline(stream);
	}
}

void			ft_mvright(t_stream *stream)
{
	unsigned int	i;

	if (stream->command) //si quelque chose est affiché
	{
		//si on est pas sur la dernière ligne ni sur un caractère aller à la ligne
		if (((stream->config->prompt_len + stream->pos) % stream->col)
			!= stream->col - 1 && stream->command[stream->pos] != '\n')
		{
			stream->tput = "nd";
			ft_tputs(stream); //on avance le curseur d'un pas à droite.
		}
		else
		{
			i = 0;
			stream->tput = "le";
			while (++i <= stream->col - 1)
				ft_tputs(stream); //on va en début de ligne.
			stream->tput = "do"; //on saute une ligne
			ft_tputs(stream);
		}
		stream->pos++;
		// Quelque soit l'évolution de la position physique du curseur à l'écran, on avance de 1 dans la commande.

	}
}
