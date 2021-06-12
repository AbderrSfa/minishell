/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:26:43 by asfaihi           #+#    #+#             */
/*   Updated: 2019/11/24 18:39:22 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		how_long(long nb)
{
	int		l;

	l = 0;
	if (nb == 0)
		l++;
	if (nb < 0)
	{
		nb = -nb;
		l++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		l++;
	}
	return (l);
}

char			*ft_itoa(int n)
{
	char	*a;
	long	nb;
	int		i;

	nb = n;
	i = how_long(nb);
	a = (char *)malloc(i + 1);
	if (a == 0)
		return (NULL);
	a[i] = '\0';
	i--;
	if (nb < 0)
	{
		a[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		a[0] = 48;
	while (nb > 0)
	{
		a[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (a);
}
