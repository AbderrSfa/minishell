/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:42:51 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/22 13:41:32 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*y;
	unsigned char	*x;

	y = (unsigned char *)src;
	x = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		if (y[i] == (unsigned char)c)
		{
			x[i] = y[i];
			return (&x[i + 1]);
		}
		x[i] = y[i];
		i++;
	}
	return (NULL);
}
