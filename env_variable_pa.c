/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 15:46:34 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*variable_expander(char *key, t_list *env_lst)
{
	t_env	*temp;
	char	*expanded;
	size_t	len;

	len = 0;
	expanded = NULL;
	while (env_lst != NULL)
	{
		temp = env_lst->content;
		if (ft_strlen(temp->key) > ft_strlen(key))
			len = ft_strlen(temp->key);
		else
			len = ft_strlen(key);
		if (!(ft_strncmp(key, temp->key, len)))
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

char	*env_var_checker(char *s, t_list *env_lst)
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
		var.result = ft_strjoin(var.result, temp = ft_substr(s, j, var.i - j));
		free(temp);
		free(temp2);
		if (s[var.i] == '$')
			get_variable(s, env_lst, &var);
	}
	return (var.result);
}
