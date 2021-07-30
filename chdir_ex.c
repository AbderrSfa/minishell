/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:52:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/18 15:19:06 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	cd(char **pwd, char **oldpwd, char *dir, char *home)
{
	int i;
	char *str;

	i = chdir(dir);
	if (i == -1)
	{
		printf("minishell: cd: %s: %s\n",dir, strerror(errno));
		return (1);
	}
	else
	{
		str = getcwd(NULL, 0);
		if (str == NULL)
		{
		//	printf("cd: error retrieving current directory: getcwd:");
			printf("yyyycannot access parent directories: No such file or directory");
			if (g_pwd == NULL)
				g_pwd = ft_strjoin("", dir);
			else 
				g_pwd = ft_strjoin("", dir);//free
		}
		else
		{
			free(g_pwd);
			g_pwd = str;
		}
		free(*oldpwd);
		*oldpwd = *pwd;
		*pwd = ft_strjoin(g_pwd,"");
	}
	return (0);
}
