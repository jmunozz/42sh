#include "minishell.h"

t_list	*ft_lexer_sshell_on(char *cmd, size_t *i, t_list **next)
{
	if ((*next)->data && ((char**)(*next)->data)[0]
			&& ft_error(SHNAME, "parse error near", "(", CR_ERROR))
		return NULL;
	(*next)->data_size = SSHELL;
	ft_freegiveone(&(*next)->data);
	(*next)->data = ft_lexer(cmd + *i);
	*i = ft_save_cmd(NULL) - cmd;
	return (*next);
}

t_list	*ft_lexer_sshell_off(char *cmd, size_t *i, t_list **next)
{
	(void)i;
	(void)cmd;
	return (*next);
}
