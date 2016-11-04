
#include "minishell.h"

static void	ft_heredoc(t_list *begin, t_config *config)
{
	char		**kill;
	char		*tmp;

	config->shell_state = SCANNING_COMMAND;
	config->heredoc = 1;
	config->pwd_subrep = "heredoc> ";
	config->prompt_len = 9;
	tmp = ft_streamscan(config, ft_save_stream(NULL), 0);
	while (!tmp || ft_strcmp(tmp, ((char**)begin->next->data)[0]))
	{
		kill = (char**)begin->next->data;
		if (!(begin->next->data =
					ft_strtabadd((char**)begin->next->data, ((tmp) ? tmp : ft_strnew(1)))))
		{
			ft_error(SHNAME, "heredoc", "malloc error", CR_ERROR);
			return ;
		}
		ft_freegiveone((void**)&kill);
		tmp = ft_streamscan(config, ft_save_stream(NULL), 0);
	}
	config->shell_state = RUNNING_COMMAND;
	ft_update_pwd(config);
	config->heredoc = 0;
}

static void	ft_decant(t_list *cmd, t_list *src)
{
	int		i;
	char	**kill;

	i = 0;
	while (((char**)src->data)[++i])
	{
		kill = (char**)cmd->data;
		cmd->data = (void*)ft_strtabadd((char**)cmd->data, ((char**)src->data)[i]);
		((char**)src->data)[i] = NULL;
		ft_freegiveone((void**)&kill);
	}
}

void		ft_herringbone(t_list *begin, t_config *config)
{
	t_list	*cmd;

	cmd = begin;
	while (begin && begin->next)
	{
		if ((begin->data_size == HEREDOC || (begin->data_size == OP
			&& (((char*)begin->data)[0] == '<'
				|| ((char*)begin->data)[0] == '>'))))
			ft_decant(cmd, begin->next);
		else if (begin->data_size == PIPE || (begin->data_size == OP
			&& ((char*)begin->data)[0] != '<' && ((char*)begin->data)[0] != '>'))
			cmd = begin->next;
		if (begin->data_size == HEREDOC)
			ft_heredoc(begin, config);
		begin = begin->next;
	}
	return ;
}
