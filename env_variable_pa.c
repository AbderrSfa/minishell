/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 12:40:06 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*variable_expander(char *key, t_list *env_list)
{
	t_env	*temp;
	char	*expanded;

	expanded = NULL;
	while (env_list != NULL)
	{
		temp = env_list->content;
		if (!(ft_strncmp(key, temp->key, ft_strlen(temp->key))))
			expanded = ft_strdup(temp->value);	
		env_list = env_list->next;
	}
	return (expanded);
}

char	*env_var_checker(char *s, t_list *env_list)
{
	int		i;
	int		j;
	char	*result;
	char	*temp;
	char	*temp2;

	result = NULL;
	temp = NULL;
	i = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		temp2 = result;
		result = ft_strjoin(result, temp = ft_substr(s, j, i - j));
		free(temp);
		free(temp2);
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != 39 && s[i] != '$')
				i++;
			temp2 = ft_substr(s, j, i - j);
			temp = variable_expander(temp2, env_list);
			free(temp2);
			temp2 = result;
			result = ft_strjoin(result, temp);
			free(temp);
			free(temp2);
		}
	}
	return (result);
}
