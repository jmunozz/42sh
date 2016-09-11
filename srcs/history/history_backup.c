#include "minishell.h"

static int	ft_safeputstr(int fd, char *str)
{
	if (str && 0 > write(fd, str, ft_strlen(str)))
	{
		FT_PUTSTRFD("minishell: wasn't abble to save history", " ", "\n", 2);
		ft_freegiveone((void **)&str);
		return (0);
	}
	ft_freegiveone((void **)&str);
	return (1);
}

void		ft_purge_history(t_config *config)
{
	int		i;
	int		fd;

	if ((fd = open(config->hloc, O_CREAT | O_WRONLY
		| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		FT_PUTSTRFD("minishell: wasn't abble to save history", " ", "\n", 2);
	else
	{
		i = config->hindex;
		while (1)
		{
			ft_incr_history(&i);
			if (!ft_safeputstr(fd, config->history[i])
				|| i == config->hindex)
				break ;
			if (config->history[i])
				write(fd, "\n", 1);
		}
		write(fd, "\0", 1);
		close(fd);
	}
}

void		ft_load_history(t_config *config)
{
	int		fd;

	if ((fd = open(config->hloc, O_RDONLY)) < 0)
		FT_PUTSTRFD("minishell: wasn't abble to load history", " ", "\n", 2);
	else
	{
		while (get_next_line(fd, &(config->history[config->hindex])) > 0)
			if (config->history[config->hindex][0])
				ft_incr_history(&(config->hindex));
		//ft_incr_history(&(config->hindex));
		close(fd);
	}
}
