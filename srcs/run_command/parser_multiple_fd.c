#include "minishell.h"

static void	ft_dup_fds(char *op, char *ampersand, char *file, int *fd)
{
	int	tmpfd;
	if (ampersand && -1 == dup2(fd[1], fd[0]))
		ft_error(SHNAME, "bad file descriptor", ft_st_itoa(fd[1]), CR_ERROR);
	else if (!ampersand)
	{
		if (!(tmpfd = ft_redirectpipe(file, NULL, op)))
			return ;
		dup2(tmpfd, fd[0]);
		close(tmpfd);
	}
}

void		ft_handle_multiplefd(char **others_fd, int *w_pipe, int *r_pipe)
{
	int		i;
	char	*op;
	char	*ampersand;
	int		fd[2];

(void)r_pipe;
(void)w_pipe;
	i = -1;
	while (others_fd[++i] && !(fd[0] = 0) && !(fd[1] = 0))
	{
		op = others_fd[i] + ft_next_op(others_fd[i], 0);
		fd[0] = ft_atoi(others_fd[i]);
		if (!fd[0] && others_fd[i][0] != '0')
			fd[0] = 1;
		if ((ampersand = ft_strchr(op, '&')) && !(*ampersand = 0))
		{
			fd[1] = ft_atoi(ampersand + 1);
			if (*(ampersand + 1) == '-')
				ft_dup_fds(op, NULL, "/dev/null", fd);
			else
				ft_dup_fds(op, ampersand, NULL, fd);
		}
		else
			ft_dup_fds(op, NULL, others_fd[++i], fd);
	}
}
