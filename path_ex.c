/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:32:32 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/02 10:48:10 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_envp(t_list *envp, char *key)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (strcmp(key, env->key) == 0)
			return (env->value);
		envp = envp->next;
	}
	return (NULL);
}

char	**get_paths(t_list *envp)
{
	char	**paths;
	char	*path;

	path = get_envp(envp, "PATH");
	if (path != NULL)
	{
		paths = ft_split(path, ':');
		return (paths);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	int		j;
	char	*str;

	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		return (cmd);
	if (cmd[0] != '\0' && paths != NULL)
	{
		cmd = ft_strjoin("/", cmd);
		i = 0;
		while (paths[i] != NULL)
		{
			str = ft_strjoin(paths[i], cmd);
			j = open(str, O_RDONLY);
			if (j != -1 && j != 13)
				return (str);
			free(str);
			i++;
		}
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
