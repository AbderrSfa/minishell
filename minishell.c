#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

int		main()
{
	char	buf[10];

	while (1)
	{
		ft_putstr("\033[0;32mminishell\033[0;0m:$ ");
		read(0, buf, 11);
	}
	return (0);
}