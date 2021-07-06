/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:43:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/06 12:11:49 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_key(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=')
		i++;
	temp = ft_substr(s, 0, i);
	return (temp);
}

char	*get_value(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=')
		i++;
	temp = ft_substr(s, i + 1, ft_strlen(s) - i);
	return (temp);
}

t_env	*make_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	initialize_env_node(new);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}

t_list	*prep_env_list(t_list *env_list, char **env)
{
	t_list	*new;
	t_env	*temp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		temp = make_env_node(key, value);
		new = ft_lstnew(temp);
		ft_lstadd_back(&env_list, new);
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}