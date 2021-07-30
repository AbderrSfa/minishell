/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:23:24 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/17 19:43:15 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo(char **argv, char option)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i] != NULL)
			write(1, " ", 1);
	}
	if (option != 'n')
		write(1, "\n", 1);
	return (0);
}
