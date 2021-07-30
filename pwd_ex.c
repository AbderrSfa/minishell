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

void pwd(void)
{
	if(g_pwd == NULL)
	{
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n",g_pwd);
}

void ft_exit(int status)
{
	exit(status);
}
