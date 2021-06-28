/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:59:37 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 16:35:30 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	long	bn;

	bn = n;
	i = 1;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n < 0)
		{
			bn = -bn;
			ft_putchar_fd('-', fd);
		}
		while ((bn / (i * 10)) != 0)
			i = (i * 10);
		while (i != 0)
		{
			ft_putchar_fd((bn / i) + 48, fd);
			bn = (bn % i);
			i = (i / 10);
		}
	}
}
