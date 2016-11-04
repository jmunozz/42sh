#include "minishell.h"

/*
**lexer.c -> lexer_av.c -> lexer_quote.c -> env_var.c
*/

char			*ft_save_cmd(char *cmd)
{
	static char *save = NULL;

	if (cmd)
		save = cmd;
	return (save);
}

void			ft_list_free_av(void *data, size_t data_size)
{
	if (!data_size && data)
		ft_strtabfree((char **)data);
	else if (data_size == OP || data_size == PIPE || data_size == HEREDOC)
		free(data);
	else if (data_size == SSHELL)
		ft_freelist((t_list *)data);
}

t_list			*ft_freelist(t_list *begin)
{
	ft_lstdel(&begin, ft_list_free_av);
	return NULL;
}

int				ft_next_op(char *cmd, size_t i)
{
	while (cmd[i] && !ft_strchr("><|&;()#", cmd[i]))
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
			i = ft_dodge_quote(cmd, i);
		else
			++i;
	}
	if (cmd[i] == '#' && i && cmd[i - 1] != ' ')
		ft_next_op(cmd, i);
	return (i);
}

t_list			*ft_lexer(char *cmd)
{
	size_t	i;
	t_list	*begin;
	t_list	*next;

dprintf(1, "\nentering lexer :\n");
	while (*cmd == ' ')
		++cmd;
	if (!*cmd || !(begin = (t_list *)ft_memalloc(sizeof(t_list))))
		return NULL;
	next = begin;
	i = 0;
	while ((cmd = cmd + i) && !(i = 0) && *cmd && *cmd != ')')
	{
		i = ft_next_op(cmd, i);
		if (i && (cmd[i] == '>' || cmd[i] == '<') && ft_isdigit(cmd[i - 1]))
			i--;
		if (!(next = ft_op_handle(cmd, &i, &next)))
			return (ft_freelist(begin));
		while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n')
			++i;
		if (cmd[i] && cmd[i] != ')'
			&& !(next->next = (t_list *)ft_memalloc(sizeof(t_list)))
			&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR))
			return (ft_freelist(begin));
		next = next->next;
	}
	ft_lexer_sshell_off(cmd, i);
	return (begin);
}
