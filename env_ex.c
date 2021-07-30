/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 15:30:10 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 17:30:58 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void ft_env(t_list *envp)
{
	t_env *env;

	envp = envp->next;
	while (envp)
	{
		env = envp->content;
		if(env->value != NULL)
		{
			printf("%s=",env->key);
			printf("%s\n",env->value);
		}
		envp = envp->next;
	}
}
