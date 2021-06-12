/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:36:27 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/24 11:52:04 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const	char *ndl, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (ndl[0] == '\0')
		return ((char *)hay);
	while (i < len && hay[i])
	{
		j = 0;
		while (hay[i + j] == ndl[j] &&
				ndl[j] && hay[i + j] && i + j < len)
			j++;
		if (ndl[j] == '\0')
			return ((char *)hay + i);
		else
			i++;
	}
	return (0);
}
