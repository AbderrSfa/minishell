/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/25 16:48:49 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '<' || s[i] == '>')
			new->redirect = redirections(new->redirect, ft_substr(s, i, ft_strlen(s)), p);
		while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '<')
		{
			j = i;
			while (s[i] != ' ' && s[i] != '"' && s[i] != 39
				&& s[i] && s[i] != '<' && s[i]!= '>')
				i++;
			new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp = ft_substr(s, j, i - j));
			if (s[i] == '"')
			{
				temp = double_quotes(s, i + 1, p);
				new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp);
			}
			if (s[i] == 39)
			{
				temp = single_quotes(s, i + 1, p);
				new->args[new->arg_num] = ft_strjoin(new->args[new->arg_num], temp);
			}
			if (!s[i] || s[i] == ' ' || s[i] == '>' || s[i] == '<')
				new->arg_num++;			
		}
		if (s[i] == '"')
		{
			new->args[new->arg_num] = double_quotes(s, i + 1, p);
			new->arg_num++;			
		}
		if (s[i] == 39)
		{
			new->args[new->arg_num] = single_quotes(s, i + 1, p);
			new->arg_num++;			
		}
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