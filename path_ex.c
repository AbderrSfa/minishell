/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:32:32 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/14 15:23:33 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char *envp[])
{
	char	**paths;

	while (*envp != NULL)
	{
		if ((*envp)[0] == 'P' && (*envp)[1] == 'A' && (*envp)[2] == 'T'
				&& (*envp)[3] == 'H' && (*envp)[4] == '=' )
		{
			paths = ft_parse(*envp + 5, ':');
			return (paths);
		}
		envp++;
	}
	ft_putstr_fd("error: PATH not found\n", 2);
	exit(0);
}

char	*get_cmd_path(const char *cmd, char **paths)
{
	int		i;
	int		j;
	char	*str;

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
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
