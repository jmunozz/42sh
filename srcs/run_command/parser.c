#include "minishell.h"

static t_list	*ft_cut_lst(t_list *begin, t_config *config)
{
	t_list	*memo;

	while (begin)
	{
		memo = begin;
		begin = begin->next;
		if (begin && begin->data_size 
			&& (!ft_strcmp(";", (char*)(begin->data))
			|| !ft_strcmp("&&", (char*)(begin->data))
			|| !ft_strcmp("||", (char*)(begin->data))))
		{
			config->dot_sequence = ((char*)(begin->data))[0];
			begin = begin->next;
			free(memo->next->data);
			ft_freegiveone((void **)&(memo->next));
			break ;
		}
	}
	return (begin);
}

char		*ft_built_sentence(t_list *begin)
{
	char	*tmp;
	char	*sentence;
	char	*tocpy;

	sentence = NULL;
	while (begin)
	{
		if (!begin->data_size)
			tocpy = ft_strtabchrjoin((char **)begin->data, ' ');
		else
			tocpy = (char *)begin->data;
		if (sentence)
			tmp = ft_strchrjoin(sentence, ' ', tocpy);
		else
			tmp = ft_strdup(tocpy);
		if (tmp && ft_freegiveone((void **)&sentence))
			sentence = tmp;
		if (!begin->data_size)
			ft_freegiveone((void **)&tocpy);
		begin = begin->next;
	}
	return (sentence);
}

int			ft_build_pipe(t_list *begin, t_config *config, int **r_pipe)
{
	t_list	*rhead;

	while (begin && begin->data_size && begin->data_size != SSHELL)
		begin = begin->next;
	if (begin && begin->next)
	{
		rhead = begin->next;
		if (!ft_node_descriptors(begin, &rhead, config, r_pipe))
			return (0);
		if (begin->next)
			begin->next->next = rhead;
		else
			begin->next = rhead;
	}
	return (1);
}

static void		ft_sentence(t_list *begin, t_config *config)
{
	t_list	*job;
	char	*sentence;
	int		*r_pipe;

	sentence = ft_built_sentence(begin);
	r_pipe = NULL;
	if (!ft_build_pipe(begin, config, &r_pipe))
		return ;
	if ((job = ft_run_sentence(begin, config, r_pipe)))
		ft_wait_sentence(job, sentence, config);
	ft_freegiveone((void**)&r_pipe);
}

void			ft_parse(t_list *begin, t_config *config)
{
	t_list	*next;
	char	test;

	config->last_exit = 0;
	test = ';';
	while ((next = ft_cut_lst(begin, config)))
	{
		if (config->shell_state == RUNNING_COMMAND
			&& (test == ';' || (test == '&' && !config->last_exit)
			|| (test == '|' && config->last_exit)))
			ft_sentence(begin, config);
		ft_freelist(begin);
		begin = next;
		test = config->dot_sequence;
	}
	if (config->shell_state == RUNNING_COMMAND
		&& (test == ';' || (test == '&' && !config->last_exit)
		|| (test == '|' && config->last_exit)))
		ft_sentence(begin, config);
	ft_freelist(begin);
}
