/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/14 17:31:32 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		get_size(char *command)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39 && command[i])
				i++;
			ret++;
		}
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"' && command[i])
				i++;
			ret++;
		}
		if (command[i] == 39)
		{
			i++;
			while (command[i] != 39 && command[i])
				i++;
			ret++;
		}
		if (command[i])
			i++;
	}
	return (ret);
}

void	allocate_array(char *s, t_simple_cmd *cmd)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	cmd->words = malloc(sizeof(char *) * (ret + 1));
	while (i < (ret + 1))
		cmd->words[i++] = malloc(sizeof(char) * ft_strlen(s));
	cmd->words[i] = NULL;
}

void	env_var_parser(t_simple_cmd *cmd, char *word)
{
	int		i;

	i = 0;
	while (word[i] && word[i] != '$')
		i++;
	if (word[i++] == '$')
	{
		cmd->env_variable = ft_substr(word, i, (ft_strlen(word) - i));
		printf("\033[0;33mEnv Var: %s\033[0;0m\n", cmd->env_variable);
	}
}

int		double_quotes(t_simple_cmd *cmd, char *command, int i)
{
	int		x;

	x = 0;
	i++;
	while (command[i] != '"' && command[i])
		cmd->words[cmd->word_num][x++] = command[i++];
	cmd->words[cmd->word_num][x] = '\0';
	if (command[i] != '"')
	{
		printf("Unclosed double quote");
		exit(EXIT_FAILURE);
	}
	env_var_parser(cmd, cmd->words[cmd->word_num]);
	cmd->word_num++;
	return (i);
}

int		single_quotes(t_simple_cmd *cmd, char *command, int i)
{
	int		x;

	x = 0;
	i++;
	while (command[i] != 39 && command[i])
		cmd->words[cmd->word_num][x++] = command[i++];
	cmd->words[cmd->word_num][x] = '\0';
	if (command[i] != 39)
	{
		printf("Unclosed single quote");
		exit(EXIT_FAILURE);
	}
	cmd->word_num++;
	return (i);
}

void	simple_cmd_lexer(t_simple_cmd *cmd, char *command)
{
	int		i;
	int		x;

	i = 0;
	cmd->word_num = 0;
	cmd->env_variable = NULL;
	x = 0;
	allocate_array(command, cmd);
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			x = 0;
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39 && command[i])
				cmd->words[cmd->word_num][x++] = command[i++];
			cmd->words[cmd->word_num][x] = '\0';
			env_var_parser(cmd, cmd->words[cmd->word_num]);
			cmd->word_num++;
		}
		if (command[i] == '"')
			i = double_quotes(cmd, command, i);
		if (command[i] == 39)
			i = single_quotes(cmd, command, i);
		if (command[i])
			i++;
	}
}