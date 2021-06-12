/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:28:11 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/24 11:58:00 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ldest;
	size_t	lsource;
	size_t	cat;
	size_t	out;

	cat = 0;
	if (dst == NULL && size == 0)
		return (ft_strlen(src));
	lsource = ft_strlen(src);
	ldest = ft_strlen(dst);
	if (size <= ldest)
		out = lsource + size;
	else
	{
		cat = size - ldest - 1;
		out = ldest + lsource;
	}
	i = 0;
	while (i < cat && src[i])
		dst[ldest++] = src[i++];
	if (cat > 0)
		dst[ldest] = '\0';
	return (out);
}
