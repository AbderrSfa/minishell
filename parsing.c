/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/25 11:49:21 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_var_parser(t_cmd *cmd, char *word)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (word[i])
	{
		while (word[i] && word[i] != '$')
			i++;
		if (word[i++] == '$')
		{
			j = i;
			while (word[j] && word[j] != ' ' && word[j] != '$')
				j++;
			cmd->env_variable = ft_substr(word, i, j - 1);
			printf("\033[0;33mEnv Var: %s\033[0;0m\n", cmd->env_variable);
		}
		temp = cmd->env_variable;
	}
}

int	double_quotes(t_cmd *cmd, char *s, int i)
{
	int		j;

	j = i;
	while (s[i] != '"' && s[i])
		i++;
	if (s[i] != '"')
	{
		printf("Unclosed double quote");
		exit(EXIT_FAILURE);
	}
	cmd->args[cmd->arg_num] = ft_substr(s, j, i - j);
	env_var_parser(cmd, cmd->args[cmd->arg_num]);
	cmd->arg_num++;
	i++;
	return (i);
}

int	single_quotes(t_cmd *cmd, char *s, int i)
{
	int		j;

	j = i;
	while (s[i] != 39 && s[i])
		i++;
	if (s[i] != 39)
	{
		printf("Unclosed single quote");
		exit(EXIT_FAILURE);
	}
	cmd->args[cmd->arg_num] = ft_substr(s, j, i - j);
	cmd->arg_num++;
	i++;
	return (i);
}

void	simple_cmd_parse(t_cmd *new, char *s)
{
	int			i;
	int			j;
	int			*p;

	i = 0;
	j = 0;
	p = &i;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '<' || s[i] == '>')
			new->redirect = redirections(new->redirect, ft_substr(s, i, ft_strlen(s)), p);
		if (s[i] && s[i] != '"' && s[i] != 39 && s[i] != '>' && s[i] != '<')
		{
			j = i;
			while (s[i] != ' ' && s[i] != '"' && s[i] != 39
				&& s[i] && s[i] != '<' && s[i]!= '>')
				i++;
			new->args[new->arg_num] = ft_substr(s, j, i - j);
			env_var_parser(new, new->args[new->arg_num]);
			new->arg_num++;
		}
		if (s[i] == '"')
			i = double_quotes(new, s, i + 1);
		if (s[i] == 39)
			i = single_quotes(new, s, i + 1);
	}
}

t_cmd	*new_node(char *s)
{
	t_cmd	*new;
	int		i;
	int		x;

	if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	initialize_node(new, s);
	i = 0;
	x = 0;
	simple_cmd_parse(new, s);
	new->cmd = new->args[0];
	return (new);
}