/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:55:20 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 08:55:23 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_printsignal(int signum, pid_t pid, t_list *process)
{
	static char	*errors[] = {ERR_SEGV};
	t_sigerr	i;
	char		*str;

	i = SEGV;
	if (signum == SEGV)
		i = SEGV;
	if (process->data_size == SENT)
	{
		str = ft_strchrjoin(ft_st_itoa(pid), ' ', ((char*)process->data));
		ft_error(SHNAME, str, errors[i], CR_ERROR);
		free(str);
	}
	else
		ft_error(SHNAME, ft_st_itoa(pid), errors[i], CR_ERROR);
}

void		ft_signal_handle(int i)
{
	t_stream *stream;

	if ((stream = ft_save_stream(NULL)) && stream->config)
	{
		if (i == SIGWINCH)
			ft_winsize();
		if (i == SIGINT)
		{
			if (stream->config->shell_state == RUNNING_COMMAND)
				stream->config->shell_state = SIGINT_COMMAND;
			else
				stream->state = REPROMPT;
		}
		if (i == SIGTSTP && stream->config->shell_state == RUNNING_COMMAND)
			stream->config->shell_state = SIGTSTP_COMMAND;
	}
	else
	{
		stream->config->shell_state = SIGINT_COMMAND;
		ft_error(SHNAME, NULL, "error while handling signal", CR_ERROR);
	}
	ft_signal();
}

void		ft_sigwinch(int mode)
{
	if (mode && SIG_ERR == signal(SIGWINCH, &ft_signal_handle))
		ft_error(SHNAME, NULL, "sigwinch fail", CR_ERROR);
	else if (!mode && SIG_ERR == signal(SIGWINCH, SIG_DFL))
		ft_error(SHNAME, NULL, "sigwinch fail", CR_ERROR);
}

void		ft_signal_reset(void)
{
	if (SIG_ERR == signal(SIGINT, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
		ft_status(1);
}

int			ft_signal(void)
{
	if (SIG_ERR == signal(SIGINT, &ft_signal_handle))
		return (ft_status(1));
	if (SIG_ERR == signal(SIGTSTP, &ft_signal_handle))
		return (ft_status(1));
	return (0);
}
