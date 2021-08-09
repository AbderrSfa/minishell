/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:55:15 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 13:42:24 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void pwd(char *gpwd)
{
	if(gpwd == NULL)
	{
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n",gpwd);
}

void ft_exit(int status)
{
	exit(status);
}
