#include "minishell.h"

static t_list	*ft_extract_job(t_config *config, char *description)
{
	int		i;
	t_list	*p;
	t_list	*m;

	p = config->jobs;
	i = 1;
	if (!description || ft_cmp_jobs(config->jobs->data, description, i))
	{
		m = (t_list*)p->data;
		config->jobs = config->jobs->next;
		free(p);
		return (m);
	}
	while ((m = p) && (p = p->next) && ++i)
	{
		if (ft_cmp_jobs(p->data, description, i))
		{
			m->next = p->next;
			m = (t_list*)p->data;
			free(p);
			return (m);
		}
	}
	return (NULL);
}

static void	ft_continue(t_config *config, char *description, int mode)
{
	t_list	*p;
	t_list	*target;

	if (!description && !(config->jobs))
		ft_error("fg", NULL, "no current jobs", CR_ERROR);
	else if (!(target = ft_extract_job(config, description)))
		ft_error("fg", "no current job", description, CR_ERROR);
	else if (mode == JOBS_FG)
	{
		p = target;
		while ((p = p->next))
			kill(*((pid_t*)p->data), SIGCONT);
		ft_wait_sentence(target, NULL, config);
	}
}

void		ft_jobs(char **argv, t_config *config)
{
	size_t	i;

	i = 1;
	ft_print_jobs(NULL, argv[i]);
	if (!argv[i])
		ft_print_list(config->jobs);
	else
		while (argv[i++])
		{
			ft_print_list(config->jobs);
			ft_print_jobs(NULL, argv[i]);
		}

}

void		ft_fgbg(char **argv, t_config *config, int mode)
{
	size_t	i;

	i = 1;
	if (!argv[i])
		ft_continue(config, NULL, mode);
	else
		while (argv[i++])
			ft_continue(config, argv[i], mode);
}
