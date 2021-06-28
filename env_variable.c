/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 16:49:27 by asfaihi          ###   ########.fr       */
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
	while (s[i])
	{
		j = i;
		while (s[i] && s[i] != '$')
			i++;
		result = ft_strjoin(result, temp = ft_substr(s, j, i - j));
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != 39 && s[i] != '$')
				i++;
			result = ft_strjoin(result, temp = variable_expander
					(temp = ft_substr(s, j, i - j)));
		}
	}
	return (result);
}
