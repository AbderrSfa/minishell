/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/16 12:46:40 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*variable_expander(char *key, t_list *env_lst)
{
	t_env	*temp;
	char	*expanded;

	expanded = NULL;
	while (env_lst != NULL)
	{
		temp = env_lst->content;
		if (!(ft_strcmp(key, temp->key)))
			expanded = ft_strdup(temp->value);
		env_lst = env_lst->next;
	}
	return (expanded);
}

void	get_variable(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	prs->var.i++;
	j = prs->var.i;
	while (s[prs->var.i] && s[prs->var.i] != ' ' && s[prs->var.i] != 39
		&& s[prs->var.i] != '$')
		prs->var.i++;
	tmp = ft_substr(s, j, prs->var.i - j);
	temp = variable_expander(tmp, env_lst);
	if (prs->outside_quote && ft_strchr(temp, ' '))
	{
		temp = remove_spaces(temp);
		prs->extra_args = ft_split(temp, ' ');
		free(temp);
		temp = prs->extra_args[0];
	}
	free(tmp);
	tmp = prs->var.result;
	prs->var.result = ft_strjoin(prs->var.result, temp);
	free(temp);
	free(tmp);
}

void	var_edge_cases(char *s, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->var.i] == '$' && s[prs->var.i + 1] == '?')
	{
		tmp = prs->var.result;
		prs->var.i += 2;
		prs->var.result = ft_strjoin(prs->var.result,
				temp = ft_itoa(prs->ret_value));
		free(temp);
		free(tmp);
	}
	if (s[prs->var.i] == '$' && s[prs->var.i + 1] == '$')
	{
		tmp = prs->var.result;
		prs->var.i += 2;
		prs->var.result = ft_strjoin(prs->var.result, temp = ft_itoa(getpid()));
		free(temp);
		free(tmp);
	}
}

void	check_var_edge_cases(char *s, t_list *env_lst, t_prs *prs)
{
	char	*tmp;

	var_edge_cases(s, prs);
	if (s[prs->var.i] == '$' && (s[prs->var.i + 1] == ' '
			|| s[prs->var.i + 1] == '\0'))
	{
		tmp = prs->var.result;
		prs->var.i++;
		prs->var.result = ft_strjoin(prs->var.result, "$");
		free(tmp);
	}
	else if (s[prs->var.i] == '$')
		get_variable(s, env_lst, prs);
}

char	*env_var_checker(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	prs->var.result = NULL;
	temp = NULL;
	prs->var.i = 0;
	while (s[prs->var.i])
	{
		j = prs->var.i;
		while (s[prs->var.i] && s[prs->var.i] != '$')
			prs->var.i++;
		tmp = prs->var.result;
		temp = ft_substr(s, j, prs->var.i - j);
		prs->var.result = ft_strjoin(prs->var.result, temp);
		free(temp);
		free(tmp);
		check_var_edge_cases(s, env_lst, prs);
	}
	return (prs->var.result);
}
