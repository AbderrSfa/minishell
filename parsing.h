#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct	s_simple_cmd
{
	char		**words;
	int			word_num;
}				t_simple_cmd;

void	simple_cmd_lexer(t_simple_cmd *cmd, char *command);
void	allocate_array(char *s, t_simple_cmd *cmd);
int		get_size(char *s);
size_t	ft_strlen(const char *s);