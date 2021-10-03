/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:55:15 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/03 19:32:09 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ignore_n(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	i;
	int	j;

	if (argv[0] != NULL)
	{
		j = ignore_n(argv);
		i = j;
		while (argv[i] != NULL)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	if (j == 0)
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
	int	j;

	i = 0;
	if (args[1] == NULL)
		exit(g_exit_status);
	if (args[2] == NULL)
	{
		if (args[1] != NULL)
			i = ft_atoi(args[1]);
		j = 0;
		while (args[1][j] != '\0')
		{
			if (!ft_isdigit(args[1][j]))
			{
				printf("minishell: exit: %s:", args[1]);
				printf("numeric argument required\n");
				exit(255);
			}
			j++;
		}
		exit(i);
	}
	printf("minishell: exit: too many arguments\n");
}
