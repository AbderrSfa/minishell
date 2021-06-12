/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:54:43 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/24 18:39:33 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_move(char *b, char *a, size_t len)
{
	size_t	i;

	if (a >= b)
	{
		i = 0;
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			b[i - 1] = a[i - 1];
			i--;
		}
	}
	return (b);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;

	a = (char *)src;
	b = (char *)dst;
	if (src == dst)
		return (dst);
	return (ft_move(b, a, len));
}
