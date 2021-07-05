/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:43:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 15:02:05 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_list_add_back_env(t_env **alst, t_env *new)
{
	t_env	*p;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			p = *alst;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

void	free_env_list(t_env *env_list)
{
	while (env_list)
	{
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = env_list->next;
	}
}

void	initialize_env_node(t_env *new)
{
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
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

t_env	*prep_env_list(t_env *env_list, char **env)
{
	t_env	*temp;
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		temp = make_env_node(key, value);
		ft_list_add_back_env(&env_list, temp);
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}