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

int		get_size(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '"' || s[i] == 39)
			ret++;
		i++;
	}
	printf("--%d--", ret);
	return (ret);
}

char	**allocate_array(char *s, char **yeet)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	yeet = malloc(sizeof(char *) * (ret + 1));
	while (i < (ret + 1))
		yeet[i++] = malloc(sizeof(char) * ft_strlen(s));
	return (yeet);
}

void	simple_cmd_lexer(char *command)
{
	int		i;
	int		y;
	int		x;
	char	**yeet;

	i = 0;
	y = 0;
	x = 0;
	yeet = allocate_array(command, yeet);
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			x = 0;
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39 && command[i])
				yeet[y][x++] = command[i++];
			y++;
		}
		if (command[i] == '"')
		{
			x = 0;
			i++;
			while (command[i] != '"' && command[i])
				yeet[y][x++] = command[i++];
			if (command[i] != '"')
			{
				printf("Unclosed double quote");
				exit(EXIT_FAILURE);
			}
			y++;
		}
		if (command[i] == 39)
		{
			x = 0;
			i++;
			while (command[i] != 39 && command[i])
				yeet[y][x++] = command[i++];
			if (command[i] != 39)
			{
				printf("Unclosed single quote");
				exit(EXIT_FAILURE);
			}
			y++;
		}
		i++;
	}
	printf("--%s--\n", yeet[0]);
	printf("--%s--\n", yeet[1]);
	printf("--%s--\n", yeet[2]);
	printf("--%s--\n", yeet[3]);

}

int		main()
{
	t_simple_cmd	cmd;

	simple_cmd_lexer("echo");
	return (0);
}