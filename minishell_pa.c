/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/24 12:23:27 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

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
	return (head);
}

int	main(int argc, char **argv, char **env)
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
			my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
	}
	free_env_lst(envp);
	return (0);
}
