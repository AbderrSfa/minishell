#include "parsing.h"

int		main(int argc, char **argv)
{
	int		i;
	t_simple_cmd	cmd;

	simple_cmd_lexer(&cmd, argv[1]);
	i = 0;
	while (i < cmd.word_num)
		printf("(%s)\n", cmd.words[i++]);
	return (0);
}