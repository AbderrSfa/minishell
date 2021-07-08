/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 12:41:55 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_arg(t_cmd *new, char *s, t_list *env_list, t_parser *parser)
{
	char	*temp;
	char	*temp2;
	int		j;

	j = parser->i;
	if (s[parser->i] != ' ' && s[parser->i] != '"' && s[parser->i] != 39 && s[parser->i]
		&& s[parser->i] != '<' && s[parser->i] != '>')
	{
		while (s[parser->i] != ' ' && s[parser->i] != '"' && s[parser->i] != 39
			&& s[parser->i] && s[parser->i] != '<' && s[parser->i] != '>')
			parser->i++;
		temp = env_var_checker(temp2 = ft_substr(s, j, parser->i - j), env_list);
		free(temp2);
		temp2 = new->args[parser->arg_num];
		new->args[parser->arg_num] = ft_strjoin(new->args[parser->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[parser->i] == '"')
	{
		temp = double_quotes(s, env_list, parser);
		temp2 = new->args[parser->arg_num];
		new->args[parser->arg_num] = ft_strjoin(new->args[parser->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[parser->i] == 39)
	{
		temp = single_quotes(s, parser);
		temp2 = new->args[parser->arg_num];
		new->args[parser->arg_num] = ft_strjoin(new->args[parser->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (!s[parser->i] || s[parser->i] == ' ' || s[parser->i] == '>' || s[parser->i] == '<')
		parser->arg_num++;
}

void	simple_cmd_parse(t_cmd *new, char *s, t_list *env_list, t_parser *parser)
{
	free(new->args[parser->arg_num]);
	new->args[parser->arg_num] = NULL;
	while (s[parser->i])
	{
		while (s[parser->i] == ' ')
			parser->i++;
		if (s[parser->i] == '<' || s[parser->i] == '>')
			new->redirect = redirections(new->redirect, s, env_list, parser);
		while (s[parser->i] && s[parser->i] != ' ' && s[parser->i] != '>' && s[parser->i] != '<')
			get_arg(new, s, env_list, parser);
		if (s[parser->i] == '"')
			new->args[parser->arg_num++] = double_quotes(s, env_list, parser);
		if (s[parser->i] == 39)
			new->args[parser->arg_num++] = single_quotes(s, parser);
	}
}

t_cmd	*new_node(char *s, t_list *env_list)
{
	t_parser	parser;
	t_cmd		*new;

	parser.i = 0;
	parser.arg_num = 0;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	initialize_node(new, s);
	simple_cmd_parse(new, s, env_list, &parser);
	new->cmd = new->args[0];
	return (new);
}
