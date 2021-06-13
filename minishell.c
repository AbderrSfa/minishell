#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

int		main()
{
	char	buf[10];

	while (1)
	{
		readline("\033[0;32mminishell\033[0;0m:$ ");
	}
	return (0);
}