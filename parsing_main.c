/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/27 14:50:43 by asfaihi          ###   ########.fr       */
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

t_list	*split_by_pipes(t_list *head, char *input, t_list *env_lst)
{
	char	**commands;
	t_cmd	*temp;
	t_list	*new;
	int		i;

	i = 0;
	input = change_pipe(input);
	commands = ft_split(input, -124);
	while (commands[i])
	{
		temp = new_node(commands[i], env_lst);
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
	free(input);
	return (head);
}

int	main(void)
{
	extern char **environ;
	int		i;
	char	*input;
	t_list	*cmds;
	t_list	*templ;
	t_cmd	*temp3;

	t_list	*env_lst;
	t_list	*temp;

	t_list	*tempredir;
	t_redir	*tempredir2;

	env_lst = NULL;
	env_lst = prep_env_lst(env_lst, environ);
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strcmp(input, ""))
			add_history(input);
		temp = env_lst;
		if (!check_syntax_errors(input))
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
			while (temp3->args[i])
			{
				if (i == 0)
					printf("\033[0;33mCommand:\033[0;0m %s\n", temp3->cmd);
				printf("Arg: %s\n", temp3->args[i++]);
			}
			while (temp3->redir != NULL)
			{
				tempredir = temp3->redir;
				tempredir2 = tempredir->content;
				printf("\033[0;36m********* Redirection %d *********\033[0;0m\n", k++);
				printf("\033[0;37mType:\033[0;0m %c\n", tempredir2->type);
				printf("\033[0;38mFile:\033[0;0m %s\n", tempredir2->file);
				temp3->redir = temp3->redir->next;
			}
			templ = templ->next;
		}
		//free_cmds(cmds);
	}
	free_env_lst(env_lst);
	return (0);
}

/* int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*cmds;
	t_list	*envp;
	t_list	*temp;

	envp = NULL;
	envp = prep_env_lst(envp, env);
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strncmp(input, "", ft_strlen(input)))
			add_history(input);
		temp = envp;
		if (!check_syntax_errors(input))
		{
			cmds = split_by_pipes(cmds, input, temp);
			//my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
	}
	free_env_lst(envp);
	return (0);
} */