/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/02 10:53:46 by asfaihi          ###   ########.fr       */
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


int	main(void)
{
	int		i;
	char	*input;
	t_cmd	*head;
	t_cmd	*templ;

	while (1)
	{
		head = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strncmp(input, "", ft_strlen(input)))
			add_history(input);
		head = split_by_pipes(head, input);
		free(input);
		i = 0;
		templ = head;
		
		int		j;
		int		k;
		j = 1;
		k = 1;
		while (templ != NULL)
		{
			printf("\033[0;35m****************** Simple command %d ******************\033[0;0m\n", j++);
			i = 0;
			while (i < templ->arg_num)
			{
				if (i == 0)
					printf("\033[0;33mCommand:\033[0;0m %s\n", templ->cmd);
				printf("Arg: %s\n", templ->args[i++]);
			}
			while (templ->redirect != NULL)
			{
				printf("\033[0;36m********* Redirection %d *********\033[0;0m\n", k++);
				printf("\033[0;37mType:\033[0;0m %c\n", templ->redirect->type);
				printf("\033[0;38mFile:\033[0;0m %s\n", templ->redirect->file);
				templ->redirect = templ->redirect->next;
			}
			templ = templ->next;
		}
		templ = head;
		
		free_args(templ);
	}
	return (0);
}
