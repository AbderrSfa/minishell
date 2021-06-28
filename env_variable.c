/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 16:22:12 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*variable_expander(char *temp)
{
	char	*expanded;

	expanded = ft_strdup("(expanded)");
	return (expanded);
}

char	*env_var_checker(char *s)
{
	int		i;
	int		j;
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		temp = ft_substr(s, j, i - j);
		result = ft_strjoin(result, temp);
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != 39 && s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			temp = variable_expander(temp);
			result = ft_strjoin(result, temp);
		}
	}
	return (result);
}