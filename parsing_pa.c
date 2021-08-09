/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/29 14:15:44 by asfaihi          ###   ########.fr       */
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
		temp2 = ft_substr(s, j, prs->i - j);
		temp = env_var_checker(temp2, env_lst, prs);
		free(temp2);
		temp2 = new->args[prs->arg_num];
		new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], temp);
		free(temp2);
		free(temp);
	}
	if (s[prs->i] == '"' || s[prs->i] == '\'')
		get_dbl_and_sgl_quotes(new, s, env_lst, prs);
	if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>' || s[prs->i] == '<')
	{
		temp = ft_substr(s, j, prs->i - j);
		prs->arg_num++;
		if (!ft_strcmp(new->args[prs->arg_num - 1], "") && (temp[0] == '$' && !ft_strchr(temp, '"') && !ft_strchr(temp, '\'')))
		{
			prs->arg_num--;
			free(new->args[prs->arg_num]);
			new->args[prs->arg_num] = NULL;
		}
		free(temp);
	}
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

void	echo_n_flag(t_cmd *new)
{
	int		i;

	if (new->args[1] == NULL)
		return ;
	if (new->args[1][0] != '-' || new->args[1][1] != 'n')
		return ;
	i = 2;
	while (new->args[1][i] && new->args[1][i] == 'n')
		i++;
	if (new->args[1][i])
		return ;
	else
	{
		free(new->args[1]);
		new->args[1] = ft_strdup("-n");
	}
}

t_cmd	*new_node(char *s, t_list *env_lst, int ret)
{
	t_prs	prs;
	t_cmd	*new;
	int		i;

	prs.i = 0;
	prs.arg_num = 0;
	prs.ambigous = 0;
	prs.ret_value = ret;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	initialize_node(new, s);
	simple_cmd_parse(new, s, env_lst, &prs);
	new->cmd = new->args[0];
	i = get_size(s);
	/// This part needs to be checked for leaks
	while (i >= prs.arg_num)
	{
		free(new->args[i]);
		new->args[i] = NULL;
		i--;
	}
	///
	if (prs.ambigous == 1)
		new->cmd = NULL;
	if (!ft_strcmp(new->cmd, "echo"))
		echo_n_flag(new);
	return (new);
}
