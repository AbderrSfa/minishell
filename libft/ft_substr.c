/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:00:00 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 16:41:34 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_smallest(const char *s, unsigned int start, size_t len)
{
	if (len > ft_strlen(s + start))
		return (ft_strlen(s + start) + 1);
	return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*x;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	i = 0;
	x = (char *)malloc(sizeof(char) * ft_smallest(s, start, len));
	if (x == 0)
		return (NULL);
	while (i < (ft_smallest(s, start, len) - 1))
	{
		x[i] = s[i + start];
		i++;
	}
	x[i] = '\0';
	return (x);
}
