#include "../../includes/minishell.h"
/*
char	*ft_strnchr(const char *s, int c, size_t size)
{
	int i;
	if (size)
	{
		i = 0;
		while (s[i] && s[i] != (char)c && i < size - 1)
			i++;
		if (s[i] == (char)c)
			return ((char*)&s[i]);
	}
	return (NULL);
}
*/
// Besoin de cette version pour que is_valid fonctionne.
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



int		ft_isalphaa(int c)
{
		if ((c < 'A' || ('Z' < c && c < 'a') || 'z' < c) && c != '.')
					return (0);
			return (1);
}

int	is_alphabefore(int j, char *file)
{
	while (--j >= 0 && !ft_isalphaa(file[j]))
	{
		if (file[j] == '*')
			return (0);
	}
	return (1);
}

int		brackets(int *i, char *glob, char c)
{
	int			min;
	int			max;
	int			match;

	match = 0;
	if (!ft_strchr(&glob[*i], ']'))
		return (0);
	while (glob[*i] != ']' && !match)
	{
		if (glob[*i + 1] && glob[*i + 2] && glob[*i + 1] == '-' && glob[*i + 2] != ']')
		{
			min = (int)glob[*i] - 1;
			max = (int)glob[*i + 2];
			while (++min <= max && !match)
				if ((int)c == min)
					match = 1;
			(*i) += 2;
		}
		else if (glob[*i] == c)
			match = 1;
		(*i)++;
	}
	while (glob[*i] != ']')
		(*i)++;
	return (match);
}

int  is_valid(int i, int j, char *glob, char *file)
{
	int test;

	if (file[j] == '\0' || file[j] == '/')
	{
		while (glob[i] && glob[i] != '/')
		{
			if (glob[i] != '*')
				return (0);
			i++;
		}
		return (1);
	}
	if (i && (glob[i] == '\0' || glob[i] == '/') &&  glob[i - 1] == '*')
		return (1);
	else if (glob[i] == '\0' || glob[i] == '/')
		return ((file[j] == '\0') ? 1 : 0);
	else if (glob[i] == '?')
		return(is_valid(++i, ++j, glob, file));
	else if (i && ft_isalphaa(glob[i]) && !is_alphabefore(i, glob))
	{
		printf("on est la");
		while ((test = ft_strlenc(&file[j], glob[i])) != -1)
		{
			printf("on est rela");
			j += test;
			if (is_valid(i + 1, ++j, glob, file))
				return (2);
		}
		return (0);
	}
	else if (glob[i] == '[')
	{
		if (brackets(&i, glob, file[j]))
			return(is_valid(++i, ++j, glob, file));
		return (0);
	}
	else if (ft_isalphaa(glob[i]))
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
		printf("%s - %zu\n", begin->data, begin->data_size);
		begin = begin->next;
	}
}

/*
int		main(int ac, char **av)
{
	char		test1[] = "coco";
	char		test2[] = "cocu";
	char		test3[] = "cacao";
	char		test4[] = "..";
	t_list		*list;
	t_list		*begin;
	//ft_list_push_back(&begin, ft_lstnew(test1, 0));
	//ft_list_push_back(&begin, ft_lstnew(test2, 0));
	//ft_list_push_back(&begin, ft_lstnew(test3, 0));
	ft_list_push_back(&begin, ft_lstnew(test4, 0));
	//ft_print_list(begin);
	if (ac > 1)
	{
		list = begin;
		printf("Execution fonction globbing...\n");
		while (list)
		{
			printf("Liste traitee = %s\n", list->data);
			list->data_size = (size_t)is_valid(0, 0, av[1], list->data);
			list = list->next;
		}
		ft_print_list(begin);
	}
	return (0);
}
*/
