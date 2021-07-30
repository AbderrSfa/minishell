/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:33:21 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 20:22:13 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_valid_env_name(char *value)
{
	int i;

	i = 0;
	while(value[i] != 0)
	{
		if(value[i] != '_' && !ft_isalnum(value[i]))
			return (1);
		i++;
	}
	return (0);
}


int ft_unset(t_list *envp, char *value)
{
	int		i;
	t_env	*env;
	t_list	*pre;

	i = ft_valid_env_name(value);
	if(i == 1)
	{
		printf("minishell: unset: '%s': not a valid identifier\n",value);
		return (1);
	}
	pre = envp;
	envp = pre->next;
	while(envp != NULL)
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
