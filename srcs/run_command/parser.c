#include "minishell.h"

static t_list	*ft_cut_lst(t_list *begin, char	*op)
{
	t_list	*memo;

	while (begin)
	{
		memo = begin;
		begin = begin->next;
		if (begin && begin->data_size && !ft_strcmp(op, (char*)(begin->data)))
		{
			begin = begin->next;
			free(memo->next->data);
			ft_freegiveone((void **)(memo->next));
			break ;
		}
	}
	return (begin);
}

int			ft_build_pipe(t_list *begin)
{
	int		*pip;

	while (begin)
	{
		if (begin->data_size && !ft_strcmp((char *)(begin->data), "|"))
		{
			if (!(pip = (int *)ft_memalloc(sizeof(int) * 2)))
				return (ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR));
			if (-1 == pipe(pip))
				return (ft_error(SHNAME, "parser", "pipe error", CR_ERROR));
			ft_freegiveone((void**)&(begin->data));
			begin->data_size = PIPE;
			begin->data = (void*)pip;
			break ;
		}
		begin = begin->next;
	}
	return (0);
}
/*
static char		*ft_build_sentence(t_list *begin)
{
	char	*tmp;
	char	*sentence;

	sentence = ft_strdup((char *);
	while (begin)
	{
		tmp = sentence;
		sentence = ft_strjoin(sentence
	}
}
*/
static void		ft_sentence(t_list *begin, t_config *config)
{
	t_list	*job;
	char	*sentence;

	sentence = NULL;
	if (ft_build_pipe(begin))
		return ;
	if ((job = ft_run_sentence(begin, config, NULL)))
		ft_wait_sentence(job, sentence, config);
}

void			ft_parse(t_list *begin, t_config *config)
{
	t_list	*next;

	while ((next = ft_cut_lst(begin, ";")))
	{
		ft_sentence(begin, config);
		ft_freelist(begin);
		begin = next;
	}
	ft_sentence(begin, config);
	ft_freelist(begin);
}
