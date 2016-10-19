#include "../../includes/minishell.h"

void	build_list(t_list **list, char *str, int mode, t_stream *stream);

int		main(int ac, char **av, char **environ)
{
	t_list	*list;
	t_stream	stream;
	t_config	fig;


	fig.env = environ;
	stream.config = &fig;
	if (av[1])
	{
		build_list(&list, av[1], ft_atoi(av[2]), &stream);
		while (list)
		{
			ft_putendl((char*)list->data);
			list = list->next;
		}
	}
	else
		ft_putstr("error");
}

