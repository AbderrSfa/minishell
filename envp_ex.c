/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 16:26:44 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int envp_sort(char **tab, int size)
{
	int		wall;
	int		current;
	char	*pivot;
	char  	*tmp;
	int		len;
	
	if (size < 2)
		return (0);
	wall = 0;
	current = 0;
	pivot = tab[size - 1];
	len = ft_strlen(pivot);
	while (current < size)
	{
		if (ft_strncmp(tab[current],pivot,len) <= 0)
		{
			if (current != wall)
			{
				tmp = tab[current];
				tab[current] = tab[wall];
				tab[wall] = tmp;
			}
			wall++;
		}
		current++;	
	}
	envp_sort(tab, wall - 1);
	envp_sort(tab + wall - 1, size - wall + 1);
	return (0);
}

int ft_display_envp(t_list *envp)
{
	int i;
	char **tab;

	envp = envp->next;
	tab = list_to_arr(envp);
	envp_sort(tab, ft_lstsize(envp) + 1);
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

		size = ft_lstsize(lst) + 1;
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
