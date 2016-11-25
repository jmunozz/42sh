#include <stdio.h>

int	nmatch(char *glob, char *comp)
{
	printf("l");
  if (*glob != '\0' && *comp == '*')
    return (nmatch(glob + 1, comp) || nmatch(glob, comp + 1));
  if (*glob == '\0' && *comp == '*')
    return (nmatch(glob, comp + 1));
  if (*glob == *comp && *glob != '\0' && *comp != '\0')
    return (nmatch(glob + 1, comp + 1));
  if (*glob == *comp && *glob == '\0' && *comp == '\0')
    return (1);
  return (0);
}

int main(int ac, char **av)
{
	if (ac > 2)
	{
		if ((nmatch(av[1], av[2])))
			printf("OK");
			}
	return (0);
}
l
