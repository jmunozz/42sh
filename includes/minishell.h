#include <sys/type.h>
#include "libft.h"
typedef struct	s_config
{
	char		**env;
	char		*prompt;
}				t_config;

int		ft_minishell(t_config *config);
