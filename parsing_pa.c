/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/14 16:10:59 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_dbl_or_sgl_quotes(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
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
		if (new->args[prs->arg_num] == NULL)
			new->args[prs->arg_num] = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = single_quotes(s, prs);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
	}
}

void	is_arg_empty(t_cmd *new, char *s, t_prs *prs, int j)
{
	char	*temp;
	int		i;

	temp = ft_substr(s, j, prs->i - j);
	prs->arg_num++;
	if (!ft_strcmp(new->args[prs->arg_num - 1], "") && (temp[0] == '$'
			&& !ft_strchr(temp, '"') && !ft_strchr(temp, '\'')))
	{
		prs->arg_num--;
		free(new->args[prs->arg_num]);
		new->args[prs->arg_num] = NULL;
	}
	if (prs->extra_args)
	{
		i = 1;
		while (prs->extra_args[i])
		{
			new->args[prs->arg_num++] = prs->extra_args[i++];
		}
		prs->extra_args = NULL;
	}
	free(temp);
}

void	get_arg(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*temp2;
	int		j;

	j = prs->i;
	if (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\'' && s[prs->i]
		&& s[prs->i] != '<' && s[prs->i] != '>')
	{
		while (s[prs->i] != ' ' && s[prs->i] != '"' && s[prs->i] != '\''
			&& s[prs->i] && s[prs->i] != '<' && s[prs->i] != '>')
			prs->i++;
		prs->outside_quote = 1;
		temp2 = ft_substr(s, j, prs->i - j);
		temp = env_var_checker(temp2, env_lst, prs);
		free(temp2);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
		prs->outside_quote = 0;
	}
	if (s[prs->i] == '"' || s[prs->i] == '\'')
		get_dbl_or_sgl_quotes(new, s, env_lst, prs);
	if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>' || s[prs->i] == '<')
		is_arg_empty(new, s, prs, j);
}

void	simple_cmd_parse(t_cmd *new, char *s, t_list *env_lst, t_prs *prs)
{
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

t_cmd	*new_node(char *s, t_list *env_lst, int ret)
{
	t_prs	prs;
	t_cmd	*new;
	int		i;

	initialize_prs_node(&prs, ret, s);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	initialize_cmd_node(new, s, env_lst);
	simple_cmd_parse(new, s, env_lst, &prs);
	new->cmd = new->args[0];
	i = get_size(s);
	while (i >= prs.arg_num)
	{
		free(new->args[i]);
		new->args[i] = NULL;
		i--;
	}
	if (prs.ambigous == 1)
		new->cmd = NULL;
	if (!ft_strcmp(new->cmd, "echo"))
		echo_n_flag(new);
	return (new);
}
