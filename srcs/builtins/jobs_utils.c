#include "minishell.h"

int		ft_cmp_jobs(t_list *s, char *description, int i)
{
	char	*sentence;

	if (!description)
		return (1);
	sentence = (char*)s->data;
	if (*description == '%' && ++description)
	{
		if (ft_isdigit(*description) && ft_atoi(description) == i)
			return (1);
		if (!ft_strstr(description, sentence))
			return (1);
	}
	else if (!ft_strncmp(description, sentence, ft_strlen(description)))
		return (1);
	return (0);
}

void	ft_print_jobs(t_list *sentence, char *description)
{
	static char	*desc = NULL;
	static int	i = 0;

	if (!sentence)
	{
		i = 1;
		desc = description;
	}
	else
	{
		if (!desc || ft_cmp_jobs(sentence, desc, i))
		{
			FT_PUTSTRFD("[", ft_st_itoa(i), "]       ", 1);
			FT_PUTSTRFD(ft_st_itoa(*((int*)sentence->next->data)), "    ", sentence->data, 1);
			ft_putchar('\n');
		}
		i++;
	}
}
