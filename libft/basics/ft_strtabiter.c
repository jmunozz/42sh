#include "libft.h"

void	ft_strtabiter(char **t, void (*f)(char *str))
{
	int	i;

	i = -1;
	while (t[++i])
		f(t[i]);
}
