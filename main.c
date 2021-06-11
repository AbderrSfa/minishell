#include "parsing.h"

int		main()
{
	int		i;
	t_simple_cmd	cmd;

	simple_cmd_lexer(&cmd, "ba boom");
	i = 0;
	while (i < cmd.word_num)
		printf("(%s)\n", cmd.words[i++]);
	return (0);
}