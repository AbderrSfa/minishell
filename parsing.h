#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct	s_simple_cmd
{
	char		**words;
	char		*env_variable;
	int			word_num;
}				t_simple_cmd;

void	simple_cmd_lexer(t_simple_cmd *cmd, char *command);
void	allocate_array(char *s, t_simple_cmd *cmd);
int		get_size(char *s);
int		double_quotes(t_simple_cmd *cmd, char *command, int i);
int		single_quotes(t_simple_cmd *cmd, char *command, int i);
void	env_var_parser(t_simple_cmd *cmd, char *word);

