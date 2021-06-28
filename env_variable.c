/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:29:21 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 11:49:46 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_var_checker(char *s)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != 39 && s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			printf("[[variable: \033[0;34m%s\033[0;0m]]\n", temp);
		}
	}
}