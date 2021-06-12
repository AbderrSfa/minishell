#include "parsing.h"

int		main()
{
	int		i;
	t_simple_cmd	cmd;

	simple_cmd_lexer(&cmd, "ba boom $SHELL '$SHELL fjk\"few\" fwf'fewf \"fewfew\"");
	i = 0;
	while (i < cmd.word_num)
		printf("(%s)\n", cmd.words[i++]);
	return (0);
}