/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:33:21 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 18:44:04 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

int	ft_valid_env_name(char *value)
{
	int	i;

	i = 0;
	while (value[i] != 0)
	{
		if (value[i] != '_' && !ft_isalnum(value[i]))
		{
			printf("minishell: '%s': not a valid identifier\n", value);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_list *envp, char *value)
{
	t_env	*env;
	t_list	*pre;

	pre = envp;
	envp = pre->next;
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, value, ft_strlen(value) + 1) == 0)
		{
			pre->next = envp->next;
			free(env->key);
			free(env->value);
			free(env);
			free(envp);
		}
		else
			pre = pre->next;
		envp = pre->next;
	}
	return (0);
}

int	ft_export(t_list *envp, char *arg)
{
	char	*key;
	char	*val;
	t_env	*env;
	t_list	*tmp;

	key = get_key(arg);
	val = get_value(arg);
	while (envp != NULL)
	{
		env = envp->content;
		if (strncmp(env->key, key, ft_strlen(key) + 1) == 0 && val != NULL)
		{
			free(env->value);
			env->value = val;
		}
		if (strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (0);
		tmp = envp;
		envp = envp->next;
	}
	env = make_env_node(key, val);
	tmp->next = ft_lstnew(env);
	free(key);
	free(val);
	return (0);
}
