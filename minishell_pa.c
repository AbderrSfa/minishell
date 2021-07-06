/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/06 12:02:11 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*change_pipe(char *s)
{
	int		i;
	int		quote;
	char	*temp;

	quote = 0;
	i = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (temp == NULL)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == 39) && quote == 0)
			quote = 1;
		else if ((s[i] == '"' || s[i] == 39) && quote == 1)
			quote = 0;
		if (s[i] == 124 && quote == 0)
			temp[i++] = -124;
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

t_list	*split_by_pipes(t_list *head, char *input, t_list *env_list)
{
	char	**commands;
	t_cmd	*temp;
	t_list	*new;
	int		i;

	i = 0;
	input = change_pipe(input);
	//There's a mem leak here
	commands = ft_split(input, -124);
	while (commands[i])
	{
		temp = new_node(commands[i], env_list);
		new = ft_lstnew(temp);
		ft_lstadd_back(&head, new);
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

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*input;
	t_list	*cmds;
	t_list	*templ;
	t_cmd	*temp3;

	t_list	*env_list;
	t_list	*temp;
	t_env	*temp2;

	t_list	*tempredir;
	t_redirect	*tempredir2;

	env_list = NULL;
	env_list = prep_env_list(env_list, env);
/* 	temp = env_list;
	while (temp != NULL)
	{
		temp2 = temp->content;
		printf("\033[0;32m%s\033[0;0m --- \033[0;34m%s\033[0;0m\n", temp2->key, temp2->value);
		temp = temp->next;
	} */
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strncmp(input, "", ft_strlen(input)))
			add_history(input);
		temp = env_list;
		cmds = split_by_pipes(cmds, input, temp);
		free(input);
		i = 0;
		int		j;
		int		k;
		j = 1;
		k = 1;
		templ = cmds;
		while (templ != NULL)
		{
			temp3 = templ->content;
			printf("\033[0;35m****************** Simple command %d ******************\033[0;0m\n", j++);
			i = 0;
			while (i < temp3->arg_num)
			{
				if (i == 0)
					printf("\033[0;33mCommand:\033[0;0m %s\n", temp3->cmd);
				printf("Arg: %s\n", temp3->args[i++]);
			}
			while (temp3->redirect != NULL)
			{
				tempredir = temp3->redirect;
				tempredir2 = tempredir->content;
				printf("\033[0;36m********* Redirection %d *********\033[0;0m\n", k++);
				printf("\033[0;37mType:\033[0;0m %c\n", tempredir2->type);
				printf("\033[0;38mFile:\033[0;0m %s\n", tempredir2->file);
				temp3->redirect = temp3->redirect->next;
			}
			templ = templ->next;
		}
		free_cmds(cmds);
	}
	free_env_list(env_list);
	return (0);
}
