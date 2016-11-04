#include "minishell.h"

char			*ft_save_cmd(char *cmd)
{
	static char *save = NULL;

	if (cmd)
		save = cmd;
	return (save);
}

t_list			*ft_lexer_sshell_on(char *cmd, size_t *i, t_list *next)
{
	size_t		j;
	t_list		*test;

	if (next->data && ((char**)next->data)[0]
			&& ft_error(SHNAME, "parse error near", "(", CR_ERROR))
		return (ft_freelist(next));
	next->data_size = SSHELL;
	ft_freegiveone(&next->data);
	next->data = ft_lexer(cmd + *i);
	*i = ft_save_cmd(NULL) - cmd;
	cmd += *i;
	while ((*cmd == ' ' || *cmd == '\t' || *cmd == '\n') && ++(*i))
		++cmd;
	j = 0;
	if (*cmd)
	{
		if (!(test = ft_built_couple(cmd, &j))
			|| (test->data && ((char**)test->data)[0]))
			return (ft_freelist(next));
		ft_list_push_back(&next, test->next);
		test->next = NULL;
		ft_freelist(test);
	}
	*i += j;
	return (next);
}

void			ft_lexer_sshell_off(char *cmd, size_t i)
{
	(void)i;
	ft_save_cmd(cmd + 1);
}
