/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:55:15 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/01 18:11:22 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **argv, char option)
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

int	ft_env(t_list *envp)
{
	t_env	*env;

	envp = envp->next;
	while (envp)
	{
		env = envp->content;
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		envp = envp->next;
	}
	return (0);
}

int	ft_pwd(char *gpwd)
{
	if (gpwd == NULL)
	{
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n", gpwd);
	return (0);
}

void	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		exit(0);
	if (args[2] == NULL)
	{
		if (args[1] != NULL)
			i = ft_atoi(args[1]);
		exit(i);
	}
	printf("minishell: exit: too many arguments\n");
}
