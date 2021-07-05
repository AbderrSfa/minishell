/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 11:43:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 11:54:38 by asfaihi          ###   ########.fr       */
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

t_env	*prep_env_list(t_env *env_list, char **env)
{
	t_env	*temp;
	int		i;
	int		j;
	char	**key_val;

	i = 0;
	while (env[i])
	{
		key_val = ft_split(env[i], '=');
		temp = make_env_node(key_val[0], key_val[1]);
		ft_list_add_back_env(&env_list, temp);
		j = 0;
		while (key_val[j])
			free(key_val[j++]);
		free(key_val);
		i++;
	}
	return (env_list);
}