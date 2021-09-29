/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:52:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 18:22:13 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_error(int index, char *dir)
{
	if (index == 1)
		printf("minishell: cd: too many arguments\n");
	else if (index == 2)
		printf("minishell: cd: %s: %s\n", dir, strerror(errno));
	else
	{
		printf("cd: error retrieving current directory: getcwd:");
		printf(" cannot access parent directories: No such file or directory\n");
	}
	return (1);
}

static char	*ft_get_dir(char *dir, t_list *envp)
{
	t_env	*env;
	char	*home;

	home = NULL;
	if (dir != NULL)
		return (dir);
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, "HOME", 5) == 0)
			home = env->value;
		envp = envp->next;
	}
	return (home);
}

static void	ft_swap(t_list *envp, char **gpwd)
{
	char	**pwd;
	char	**oldpwd;
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, "PWD", 4) == 0)
			pwd = &env->value;
		else if (ft_strncmp(env->key, "OLDPWD", 7) == 0)
			oldpwd = &env->value;
		envp = envp->next;
	}
	free(*oldpwd);
	*oldpwd = *pwd;
	*pwd = ft_strjoin(*gpwd, "");
}

static void	ft_change(char *str, char *dir, char **gpwd, t_list *envp)
{
	char	*tmp;

	if (str == NULL)
	{
		ft_error(3, NULL);
		if (*gpwd == NULL)
			*gpwd = ft_strjoin("", dir);
		else
		{
			tmp = ft_strjoin("/", dir);
			*gpwd = ft_strjoin(*gpwd, tmp);
			free(tmp);
		}
	}
	else
	{
		free(*gpwd);
		*gpwd = str;
	}
	ft_swap(envp, gpwd);
}

int	ft_chdir(t_cmd *cmd, t_list *envp, char **path)
{
	int		i;
	char	*str;
	char	*dir;

	dir = ft_get_dir(cmd->args[1], envp);
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
		return (ft_error(1, NULL));
	i = chdir(dir);
	if (i == -1)
		return (ft_error(2, cmd->args[1]));
	str = getcwd(NULL, 0);
	ft_change(str, dir, path, envp);
	return (0);
}
