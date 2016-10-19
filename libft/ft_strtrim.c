/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:02:41 by rbaran            #+#    #+#             */
/*   Updated: 2016/03/15 10:19:22 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_strtrim_last(char const *s)
{
	int		res;

	if (!s)
		return (0);
	res = ft_strlen(s) - 1;
	while (res >= 0 && (s[res] == ' ' || s[res] == '\t' || s[res] == '\n'))
		res--;
	return (res + 1);
}

static int	ft_strtrim_begin(char const *s)
{
	int		res;

	res = 0;
	if (!s)
		return (res);
	while (s[res] == ' ' || s[res] == '\t' || s[res] == '\n')
		res++;
	return (res);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		idx_start;
	int		idx_last;

	if (!s)
		return (NULL);
	idx_start = ft_strtrim_begin(s);
	idx_last = ft_strtrim_last(s);
	if (idx_start < idx_last)
	{
		str = (char*)malloc(sizeof(*str) * (idx_last - idx_start + 1));
		if (str)
		{
			str = ft_strncpy(str, (s + idx_start), (idx_last - idx_start));
			str[idx_last - idx_start] = '\0';
		}
	}
	else
		str = "";
	return (str);
}
