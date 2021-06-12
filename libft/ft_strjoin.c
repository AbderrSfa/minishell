/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:47:21 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/25 13:03:11 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	l;
	char	*a;

	if (s1 != NULL && s2 != NULL)
	{
		a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (a == NULL)
			return (NULL);
		i = 0;
		l = 0;
		while (s1[i])
		{
			a[i] = s1[i];
			i++;
		}
		while (s2[l])
		{
			a[i + l] = s2[l];
			l++;
		}
		a[i + l] = '\0';
		return (a);
	}
	return (NULL);
}
