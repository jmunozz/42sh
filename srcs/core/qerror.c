#include "minishell.h"

char	*ft_qerr(char *err)
{
	if (!ft_strcmp(err, PAR_ERR))
		return ("(");
	if (!ft_strcmp(err, BACK_ERR))
		return ("\\");
	return (")");
}
