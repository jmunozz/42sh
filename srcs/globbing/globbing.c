#include "../../includes/minishell.h"


int		ft_strlenc(char *str, char c)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_alphabefore(int j, char *file)
{
	while (--j && !ft_isalpha(file[j]))
	{
		if (file[j] == '*')
			return (0);
	}
	return (1);
}

int  is_valid(int i, int j, char *glob, char *file)
{
	int test;

	if (file[j] == '\0')
	{
		printf("fin file\n");
		while (glob[i])
		{
			if (glob[i] != '*')
				return (0);
			i++;
		}
		return (1);
	}
	if (i && glob[i] == '\0' &&  glob[i - 1] == '*')
	{
		printf("fin glob\n");
		return (1);
	}
	else if (glob[i] == '\0')
	{
		printf("fin glob 2\n");
		return ((file[j] == '\0') ? 1 : 0);
	}
	else if (glob[i] == '?')
		return(is_valid(++i, ++j, glob, file));
	else if (i && ft_isalpha(glob[i]) && !is_alphabefore(i, glob))
	{
		while ((test = ft_strlenc(&file[j], glob[i])) != -1)
		{
			printf("%s -- test %d\n", &file[j], test);
			j += test;
			if (is_valid(i + 1, ++j, glob, file))
				return (2);
		}
		return (0);
	}
	else if (ft_isalpha(glob[i]))
	{
		if (glob[i] == file[j])
			return(is_valid(++i, ++j, glob, file));
		return (0);
	}
	else if (glob[i] == '*')
		return (is_valid(++i, j, glob, file));
	else
		return (0);
}

void	ft_print_list(t_list *begin)
{
	printf("--Impression de la liste--\n");
	while (begin)
	{
		if (begin->data_size > 0)
			printf("%s - %zu\n", begin->data, begin->data_size);
		begin = begin->next;
	}
}


int		main(int ac, char **av)
{
	char		test1[] = "coco";
	char		test2[] = "cocu";
	char		test3[] = "cacao";
	char		test4[] = "cococo";
	t_list		*list;
	t_list		*begin;

	ft_list_push_back(&begin, ft_lstnew(test1, 0));
	//ft_list_push_back(&begin, ft_lstnew(test2, 0));
	//ft_list_push_back(&begin, ft_lstnew(test3, 0));
	ft_list_push_back(&begin, ft_lstnew(test4, 0));
	//ft_print_list(begin);
	if (ac)
	{
		list = begin;
		printf("Execution fonction globbing...\n");
		while (list)
		{
			list->data_size = (size_t)is_valid(0, 0, av[1], list->data);
			list = list->next;
		}
		ft_print_list(begin);
	}
	return (0);
}

