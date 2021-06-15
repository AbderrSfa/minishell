/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/15 16:51:47 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		main()
{
	int		i;
	char	*input;
	t_cmd	cmd;

	while (1)
	{
		input = readline("\033[0;32mminishell\033[0;0m:$ ");
		simple_cmd_lexer(&cmd, input);
		cmd.cmd = cmd.args[0];
		i = 0;
		while (i < cmd.arg_num)
		{
			if (i == 0)
				printf("\033[0;33mCommand:\033[0;0m %s\n", cmd.cmd);
			printf("Arg: %s\n", cmd.args[i++]);
		}
	}
	return (0);
}