/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 13:24:46 by asfaihi          ###   ########.fr       */
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

/* void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\b\b  \b\b", 6);
		write(0, "\n", 1);
		write(0, "minishell-1.0$ ", ft_strlen("minishell-1.0$ "));
	}
	else
		write(0, "\b\b  \b\b", 6);
} */

void	check_syntax_errors(t_cmd *cmd)
{
	int		i;


	i = 0;
	while (cmd)
	{
		while (cmd->redirect)
		{
			if (cmd->redirect->file == NULL)
			{
				ft_putstr("minishell: syntax error near unexpected token `");
				if (cmd->redirect->type == 'G')
					ft_putchar('>');
				if (cmd->redirect->type == 'L')
					ft_putchar('<');
				if (cmd->redirect->type == 'D' || cmd->redirect->type == 'H')
					ft_putstr("newline");
				ft_putchar(39);
			}
			cmd->redirect = cmd->redirect->next;
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*input;
	t_cmd	*cmds;
	t_cmd	*templ;
	t_env	*env_list;
	t_env	*temp;

	env_list = NULL;
	env_list = prep_env_list(env_list, env);
	while (1)
	{
		cmds = NULL;
 		//signal(SIGQUIT, signal_handler);
		//signal(SIGINT, signal_handler);
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
/* 		temp = env_list;
		while (temp != NULL)
		{
			printf("\033[0;32m%s\033[0;0m --- \033[0;34m%s\033[0;0m\n", temp->key, temp->value);
			temp = temp->next;
		} */
		free_cmds(cmds);
	}

	free_env_list(env_list);
	return (0);
}
