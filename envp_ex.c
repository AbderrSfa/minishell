/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 19:54:21 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int ft_display_envp(t_list *envp)
{
	int i;
	char **tab;

	tab = list_to_arr(envp);
	i = 0;
	while (tab[i] != NULL)
	{
		printf("declare -x %s\n",tab[i]);
		i++;
	}
	return (0);
}

char **list_to_arr(t_list *lst)
{
		int		i;
		int		size;
		char *tmp;
		char	**tab;
		t_env	*env;

		size = ft_lstsize(lst);
		lst = lst->next;
		tab = malloc(size * sizeof(char*));
		i = 0;
		while(i < size - 1)
		{
				env = lst->content;
				tmp = ft_strjoin(env->key,"=");
				tab[i] = ft_strjoin(tmp, env->value);
				free(tmp);
				lst = lst->next;
				i++;
		}
		tab[i] = NULL;
		return (tab);
}
