/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/27 14:41:55 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_dbl_and_sgl_quotes(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*temp2;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env_lst, prs);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[prs->i] == 39)
	{
		temp = single_quotes(s, prs);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
	}
}

void	get_arg(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*temp2;
	int		j;

	j = prs->i;
	if (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != 39 && s[prs->i]
		&& s[prs->i] != '<' && s[prs->i] != '>')
	{
		while (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != 39
			&& s[prs->i] && s[prs->i] != '<' && s[prs->i] != '>')
			prs->i++;
		temp = env_var_checker(temp2 = ft_substr(s, j, prs->i - j), env_lst);
		free(temp2);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
	}
	get_dbl_and_sgl_quotes(new, s, env_lst, prs);
	if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>' || s[prs->i] == '<')
		prs->arg_num++;
	if (!ft_strcmp(new->args[prs->arg_num - 1], ""))
		prs->arg_num--;
}

void	simple_cmd_parse(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
/* 	free(new->args[prs->arg_num]);
	new->args[prs->arg_num] = NULL; */
	while (s[prs->i])
	{
		while (s[prs->i] == ' ')
			prs->i++;
		if (s[prs->i] == '<' || s[prs->i] == '>')
			new->redir = redirections(new->redir, s, env_lst, prs);
		while (s[prs->i] && s[prs->i] != ' '
			&& s[prs->i] != '>' && s[prs->i] != '<')
			get_arg(new, s, env_lst, prs);
	}
}

t_cmd	*new_node(char *s, t_list *env_lst)
{
	t_prs	prs;
	t_cmd	*new;
	int		i;

	i = 0;
	prs.i = 0;
	prs.arg_num = 0;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	initialize_node(new, s);
	simple_cmd_parse(new, s, env_lst, &prs);
	new->cmd = new->args[0];
	while (new->args[i])
	{
		if (!ft_strcmp(new->args[i], ""))
		{
			free(new->args[i]);
			new->args[i] = NULL;
		}
		i++;
	}
	return (new);
}
