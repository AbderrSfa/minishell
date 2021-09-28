/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_args_pa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:51:28 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 12:16:44 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	args_counter(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int	count_extra_args(char *s, int i, int j, t_list *env_lst)
{
	char	*temp;
	char	*tmp;
	int		ret;

	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != '"'
				&& s[i] != '\'' && s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			tmp = variable_expander(temp, env_lst);
			free(temp);
			if (ft_strchr(tmp, ' '))
				ret += args_counter(tmp);
			free(tmp);
		}
	}
	return (ret);
}

char	*remove_spaces(char *s)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	temp = s;
	s = ft_strtrim(s, " ");
	free(temp);
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	free(s);
	return (res);
}

void	add_extra_args(t_cmd *new, t_prs *prs)
{
	int		i;

	i = 1;
	while (prs->extra_args[i])
	{
		new->args[prs->arg_num + i] = prs->extra_args[i];
		i++;
	}
	i = 1;
	while (prs->extra_args[i])
	{
		prs->arg_num++;
		i++;
	}
	free(prs->extra_args);
	prs->extra_args = NULL;
}

void	fill_arg(char *temp, t_cmd *new, t_list *env_lst, t_prs *prs)
{
	char	*tmp;

	tmp = env_var_checker(temp, env_lst, prs);
	free(temp);
	temp = new->args[prs->arg_num];
	new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], tmp);
	free(temp);
	free(tmp);
}
