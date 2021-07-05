/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 16:09:40 by asfaihi          ###   ########.fr       */
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

t_cmd	*split_by_pipes(t_cmd *head, char *input, t_env *env_list)
{
	char	**commands;
	t_cmd	*temp;
	int		i;

	i = 0;
	input = change_pipe(input);
	//There's a mem leak here
	commands = ft_split(input, -124);
	//t_list *head ???
	//t_LIST *new;
	//new = ft_lstnew(temp);
	//ft_lst_add_back(&head ,new);
	while (commands[i])
	{
		temp = new_node(commands[i], env_list);
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

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*input;
	//t_cmd	*cmds;
	//t_cmd	*templ;
	t_env	*temp2;
	t_list	*env_list;
	t_list	*temp;

	env_list = NULL;
	env_list = prep_env_list(env_list, env);
	temp = env_list;
	while (temp != NULL)
	{
		temp2 = temp->content;
		printf("\033[0;32m%s\033[0;0m --- \033[0;34m%s\033[0;0m\n", temp2->key, temp2->value);
		temp = temp->next;
	}
/* 	while (1)
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
		free_cmds(cmds);
	} */
	free_env_list(env_list);
	return (0);
}
