/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/15 17:26:41 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	int		i;
	int		j;
	char	*input;
	char	*temp;
	t_cmd	cmd;

	j = 0;
	while (j < 5)
	{
		input = readline("\033[0;32mminishell\033[0;0m:$ ");
		simple_cmd_lexer(&cmd, input);
		temp = input;
		free(temp);
		cmd.cmd = cmd.args[0];
		i = 0;
		while (i < cmd.arg_num)
		{
			if (i == 0)
				printf("\033[0;33mCommand:\033[0;0m %s\n", cmd.cmd);
			printf("Arg: %s\n", cmd.args[i++]);
		}
		free_args(&cmd);
		j++;
	}
	return (0);
}
