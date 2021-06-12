/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:21:28 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/23 15:22:10 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	x = src;
	y = dst;
	i = 0;
	if (src == dst)
		return (dst);
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	while (i < n)
	{
		y[i] = x[i];
		i++;
	}
	return (y);
}
