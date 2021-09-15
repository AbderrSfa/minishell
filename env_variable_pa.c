/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/15 16:14:20 by asfaihi          ###   ########.fr       */
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

void	get_variable(char *s, t_list *env_lst, t_var *var, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;

	var->i++;
	j = var->i;
	while (s[var->i] && s[var->i] != ' ' && s[var->i] != 39 && s[var->i] != '$')
		var->i++;
	tmp = ft_substr(s, j, var->i - j);
	temp = variable_expander(tmp, env_lst);
	if (prs->outside_quote && ft_strchr(temp, ' '))
	{
		temp = remove_spaces(temp);
		prs->extra_args = ft_split(temp, ' ');
		free(temp);
		temp = prs->extra_args[0];
	}
	free(tmp);
	tmp = var->result;
	var->result = ft_strjoin(var->result, temp);
	free(temp);
	free(tmp);
}

void	var_edge_cases(char *s, t_var *var, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[var->i] == '$' && s[var->i + 1] == '?')
	{
		tmp = var->result;
		var->i += 2;
		var->result = ft_strjoin(var->result, temp = ft_itoa(prs->ret_value));
		free(temp);
		free(tmp);
	}
	if (s[var->i] == '$' && s[var->i + 1] == '$')
	{
		tmp = var->result;
		var->i += 2;
		var->result = ft_strjoin(var->result, temp = ft_itoa(getpid()));
		free(temp);
		free(tmp);
	}
}

void	check_var_edge_cases(char *s, t_var *var, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	var_edge_cases(s, var, prs);
	if (s[var->i] == '$' && (s[var->i + 1] == ' '
			|| s[var->i + 1] == '\0'))
	{
		tmp = var->result;
		var->i++;
		var->result = ft_strjoin(var->result, "$");
		free(tmp);
	}
	else if (s[var->i] == '$')
		get_variable(s, env_lst, var, prs);
}

char	*env_var_checker(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*tmp;
	t_var	var;

	var.result = NULL;
	temp = NULL;
	var.i = 0;
	while (s[var.i])
	{
		j = var.i;
		while (s[var.i] && s[var.i] != '$')
			var.i++;
		tmp = var.result;
		temp = ft_substr(s, j, var.i - j);
		var.result = ft_strjoin(var.result, temp);
		free(temp);
		free(tmp);
		check_var_edge_cases(s, &var, env_lst, prs);
	}
	return (var.result);
}
