#include "parsing.h"

int		main()
{
	int		i;
	char	*input;
	t_simple_cmd	cmd;

	while (1)
	{
		input = readline("\033[0;32mminishell\033[0;0m:$ ");
		simple_cmd_lexer(&cmd, input);
		i = 0;
		while (i < cmd.word_num)
			printf("(%s)\n", cmd.words[i++]);
	}
	return (0);
}