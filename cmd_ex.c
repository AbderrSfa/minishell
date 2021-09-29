/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 18:08:35 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	*create_pipes(int nbr_pipes)
{
	int	*pfds;
	int	i;
	int	j;

	pfds = malloc(2 * nbr_pipes * sizeof(int));
	i = 0;
	while (i < nbr_pipes)
	{
		j = pipe(pfds + 2 * i);
		if (j < 0)
		{
			perror("pipe: ");
			exit(0);
		}
		i++;
	}
	return (pfds);
}

void	close_pfds(int *pfds, int nbr)
{
	int	i;

	i = 0;
	while (i < 2 * nbr)
	{
		close(pfds[i]);
		i++;
	}
}

void	wait_cmds(int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds)
	{
		wait(NULL);
		i++;
	}
}

int	create_childs(t_list *cmds, int *pfds, t_list *envp)
{
	int	i;
	int	pid;

	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(cmds, pfds, envp, i);
		cmds = cmds->next;
		i += 2;
	}
	return (pid);
}
