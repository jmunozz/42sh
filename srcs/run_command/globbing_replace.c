#include "minishell.h"

int			ft_checkglob(char *arg)
{
	char	*glob;
	char	*ret;
	char	*tmp;

	tmp = arg;
	glob = "*[]?\n";
	while (*glob)
	{
		while ((ret = ft_strchr(tmp, *glob)))
		{
			if ((ft_strcmp(ret, tmp) && *(ret - 1) != '\\') 
			|| (!ft_strcmp(ret, tmp)))
				return (1);
			tmp = ret + 1;
		}
		glob++;
	}
	return (0);
}

int			ft_insertglob(t_list *begin)
{
	int		i;
	char	**t;
	char	*tmp;
	char	**g_tab;
	char	**tmp_tab;
//	int		size;

	while (begin)
	{
		if (!begin->data_size)
		{
			t = ((char **)begin->data);
			i = 0;
			while (t[i])
			{
				//size = ft_strtablen(t);
				printf("t[i] = %s\n", t[i]);
				if (!ft_checkglob(t[i]) || !(tmp = ft_launch_glob(t[i])))
					i++;
				else 
				{
					printf("tmp : %s \n", tmp);
					g_tab = ft_strsplit(tmp, ' ');
					//size += ft_strtablen(g_tab);
					printf("g_tab : \n");
					ft_putstrtab(g_tab, '\n');
					ft_putchar('\n');
					printf("t : \n");
					ft_putstrtab(t, '\n');
					ft_putchar('\n');
					//ft_freegiveone((void **)&tmp); IL faudra la free mais pas la !
					tmp_tab = t;
					printf("i = %d \n", i);
					t = ft_insertdeletetab(t, g_tab, i);
					//t[size - 1] = NULL;
				//	ft_putstrtab(t, ' ');
					i += ft_strtablen(g_tab);
					printf("i = %d \n", i);
				printf("t[i - 2] = %s\n", t[i - 2]);
				printf("t[i - 1] = %s\n", t[i - 1]);
					//ft_free(g_tab);
					//ft_free(tmp_tab);
				}
			}
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}
