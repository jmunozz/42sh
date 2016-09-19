#include "libft.h"

char	*ft_strinsert(char *dest, char *str, char *pos)
{
	char	*res;

	if (pos - dest < 0
		|| !(res = ft_strnew(ft_strlen(dest) + ft_strlen(str))))
		return NULL;
	res = ft_strncpy(res, dest, pos - dest);
	res = ft_strcat(res, str);
	res = ft_strcat(res, pos);
	return (res);
}
