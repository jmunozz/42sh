#include "includes/libft.h"

int		main(int ac, char **av)
{
	char **tab;

	if (av[1])
	{
		tab = ft_strsplit(av[1], ' ');
		while (*tab)
		{
			ft_putstr(*tab);
			tab++;
		}
		return (0);
	}
}

