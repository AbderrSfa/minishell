/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/16 17:34:10 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	split_by_pipes(t_cmd *cmd, char *input)
{
	char	**commands;
	int		i;

	i = 0;
	commands = ft_split(input, '|');
	while (commands[i])
		simple_cmd_lexer(cmd, commands[i++]);
	if (commands)
	{
		while (commands[i])
			free(commands[i++]);
		free(commands);
	}
}

int	main(void)
{
	int		i;
	int		j;
	char	*input;
	char	*temp;
	t_cmd	cmd;

	j = 0;
	while (1)
	{
		input = readline("\033[0;32mminishell\033[0;0m:$ ");
		split_by_pipes(&cmd, input);
		temp = input;
		//free(temp);
		cmd.cmd = cmd.args[0];
		i = 0;
		while (i < cmd.arg_num)
		{
			if (i == 0)
				printf("\033[0;33mCommand:\033[0;0m %s\n", cmd.cmd);
			printf("Arg: %s\n", cmd.args[i++]);
		}
		//free_args(&cmd);
		j++;
	}
	return (0);
}
