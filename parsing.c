/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/30 16:23:42 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_arg(t_cmd *new, char *s, int i, int *p)
{
	char	*temp;
	char	*temp2;
	int		j;
	int		*p2;

	j = i;
	p2 = &i;
	if (s[i] != ' ' && s[i] != '"' && s[i] != 39 && s[i]
		&& s[i] != '<' && s[i] != '>')
	{
		while (s[i] != ' ' && s[i] != '"' && s[i] != 39
			&& s[i] && s[i] != '<' && s[i] != '>')
			i++;
		temp = env_var_checker(temp2 = ft_substr(s, j, i - j));
		free(temp2);
		temp2 = new->args[new->arg_num];
		new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[i] == '"')
	{
		temp = double_quotes(s, i + 1, p2);
		temp2 = new->args[new->arg_num];
		new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[i] == 39)
	{
		temp = single_quotes(s, i + 1, p2);
		temp2 = new->args[new->arg_num];
		new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (!s[i] || s[i] == ' ' || s[i] == '>' || s[i] == '<')
		new->arg_num++;
	*p = i;
}

void	simple_cmd_parse(t_cmd *new, char *s)
{
	char		*temp;
	int			i;
	int			j;
	int			*p;

	i = 0;
	j = 0;
	p = &i;
	temp = NULL;
	new->args[new->arg_num] = NULL;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '<' || s[i] == '>')
		{
			temp = ft_substr(s, i, ft_strlen(s));
			new->redirect = redirections(new->redirect, temp, p);
			free(temp);
		}
		while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '<')
			get_arg(new, s, i, p);
		if (s[i] == '"')
			new->args[new->arg_num++] = double_quotes(s, i + 1, p);
		if (s[i] == 39)
			new->args[new->arg_num++] = single_quotes(s, i + 1, p);
	}
}

t_cmd	*new_node(char *s)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	initialize_node(new, s);
	simple_cmd_parse(new, s);
	new->cmd = new->args[0];
	return (new);
}
