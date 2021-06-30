/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/30 16:32:04 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*split_by_pipes(t_cmd *head, char *input)
{
	char	**commands;
	t_cmd	*temp;
	int		i;

	i = 0;
	commands = ft_split(input, '|');
	while (commands[i])
	{
		temp = new_node(commands[i]);
		ft_list_add_back(&head, temp);
		i++;
	}
	i = 0;
	if (commands)
	{
		while (commands[i])
			free(commands[i++]);
		free(commands);
	}
	return (head);
}


void	program_loop()
{
	char	*input;
	t_cmd	*head;

	while (1)
	{
		head = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strncmp(input, "", ft_strlen(input)))
			add_history(input);
		head = split_by_pipes(head, input);
		free(input);		
		free_args(head);
	}
}
