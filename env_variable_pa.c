/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/08/31 12:22:41 by asfaihi          ###   ########.fr       */
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

void	get_variable(char *s, t_list *env_lst, t_var *var)
{
	int		j;
	char	*temp;
	char	*temp2;

	var->i++;
	j = var->i;
	while (s[var->i] && s[var->i] != ' ' && s[var->i] != 39 && s[var->i] != '$')
		var->i++;
	temp2 = ft_substr(s, j, var->i - j);
	temp = variable_expander(temp2, env_lst);
	free(temp2);
	temp2 = var->result;
	var->result = ft_strjoin(var->result, temp);
	free(temp);
	free(temp2);
}

void	check_var_edge_cases(char *s, t_var *var, t_list *env_lst, t_prs *prs)
{
	if (s[var->i] == '$' && s[var->i + 1] == '?')
	{
		var->i += 2;
		var->result = ft_strjoin(var->result, ft_itoa(prs->ret_value));
	}
	else if (s[var->i] == '$' && s[var->i + 1] == '$')
	{
		var->i += 2;
		var->result = ft_strjoin(var->result, ft_itoa(getpid()));
	}
	else if (s[var->i] == '$' && (s[var->i + 1] == ' '
			|| s[var->i + 1] == '\0'))
	{
		var->i++;
		var->result = ft_strjoin(var->result, "$");
	}
	else if (s[var->i] == '$')
		get_variable(s, env_lst, var);
}

char	*env_var_checker(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*temp2;
	t_var	var;

	var.result = NULL;
	temp = NULL;
	var.i = 0;
	while (s[var.i])
	{
		j = var.i;
		while (s[var.i] && s[var.i] != '$')
			var.i++;
		temp2 = var.result;
		temp = ft_substr(s, j, var.i - j);
		var.result = ft_strjoin(var.result, temp);
		free(temp);
		free(temp2);
		check_var_edge_cases(s, &var, env_lst, prs);
	}
	return (var.result);
}
