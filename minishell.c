/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/14 17:31:15 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		main()
{
	int		i;
	char	*input;
	t_simple_cmd	cmd;

	while (1)
	{
		input = readline("\033[0;32mminishell\033[0;0m:$ ");
		simple_cmd_lexer(&cmd, input);
		i = 0;
		while (i < cmd.word_num)
			printf("(%s)\n", cmd.words[i++]);
	}
	return (0);
}