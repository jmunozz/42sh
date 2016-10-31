#include "libft.h"

size_t		ft_list_strlen(t_list *begin)
{
	size_t	len;

	len = 0;
	while (begin)
	{
		if (begin->data)
			len += ft_strlen((char *)begin->data);
		begin = begin->next;
	}
	return (len);
}
