#include "parsing.h"

size_t			ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

int		get_size(char *command)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39 && command[i])
				i++;
			ret++;
		}
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"' && command[i])
				i++;
			ret++;
		}
		if (command[i] == 39)
		{
			i++;
			while (command[i] != 39 && command[i])
				i++;
			ret++;
		}
		if (command[i])
			i++;
	}
	return (ret);
}

void	allocate_array(char *s, t_simple_cmd *cmd)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	cmd->words = malloc(sizeof(char *) * (ret + 1));
	while (i < (ret + 1))
		cmd->words[i++] = malloc(sizeof(char) * ft_strlen(s));
	cmd->words[i] = NULL;
}

void	simple_cmd_lexer(t_simple_cmd *cmd, char *command)
{
	int		i;
	int		x;

	i = 0;
	cmd->word_num = 0;
	x = 0;
	allocate_array(command, cmd);
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			x = 0;
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39 && command[i])
				cmd->words[cmd->word_num][x++] = command[i++];
			cmd->words[cmd->word_num][x] = '\0';
			cmd->word_num++;
		}
		if (command[i] == '"')
		{
			x = 0;
			i++;
			while (command[i] != '"' && command[i])
				cmd->words[cmd->word_num][x++] = command[i++];
			cmd->words[cmd->word_num][x] = '\0';
			if (command[i] != '"')
			{
				printf("Unclosed double quote");
				exit(EXIT_FAILURE);
			}
			cmd->word_num++;
		}
		if (command[i] == 39)
		{
			x = 0;
			i++;
			while (command[i] != 39 && command[i])
				cmd->words[cmd->word_num][x++] = command[i++];
			cmd->words[cmd->word_num][x] = '\0';
			if (command[i] != 39)
			{
				printf("Unclosed single quote");
				exit(EXIT_FAILURE);
			}
			cmd->word_num++;
		}
		if (command[i])
			i++;
	}
}