/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/05 11:57:11 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	envp_sort(char **tab, int size)
{
	int		len;
	int		wall;
	int		current;
	char	*pivot;

	if (size < 2)
		return (0);
	wall = 0;
	current = 0;
	pivot = tab[size - 1];
	len = ft_strlen(pivot);
	while (current < size)
	{
		if (ft_strncmp(tab[current], pivot, len) <= 0)
		{
			if (current != wall)
				ft_swap(&tab[current], &tab[wall]);
			wall++;
		}
		current++;
	}
	envp_sort(tab, wall - 1);
	envp_sort(tab + wall - 1, size - wall + 1);
	return (0);
}

int	ft_display_envp(t_list *envp)
{
	int		i;
	int		j;
	char	**tab;

	envp = envp->next;
	tab = list_to_arr(envp);
	envp_sort(tab, ft_lstsize(envp) + 1);
	i = 0;
	while (tab[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (tab[i][j] != '=' && tab[i][j] != '\0')
		{
			ft_putchar(tab[i][j]);
			j++;
		}
		if (tab[i][j] != '\0')
			printf("=\"%s\"\n", &tab[i][j + 1]);
		else
			ft_putchar('\n');
		i++;
	}
	return (0);
}

static char	*ft_join(t_env *env)
{
	char	*tab;
	char	*tmp;

	if (env->value != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		tab = ft_strjoin(tmp, env->value);
		free(tmp);
		return (tab);
	}
	return (env->key);
}

char	**list_to_arr(t_list *lst)
{
	int		i;
	int		size;
	char	*tmp;
	char	**tab;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	tab = malloc(size * sizeof(char *));
	i = 0;
	while (i < size - 1)
	{
		env = lst->content;
		tab[i] = ft_join(env);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
