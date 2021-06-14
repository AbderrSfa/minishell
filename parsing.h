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

int		get_size(char *s);
void	allocate_array(char *s, t_simple_cmd *cmd);
void	env_var_parser(t_simple_cmd *cmd, char *word);
void	simple_cmd_lexer(t_simple_cmd *cmd, char *command);
int		double_quotes(t_simple_cmd *cmd, char *command, int i);
int		single_quotes(t_simple_cmd *cmd, char *command, int i);

