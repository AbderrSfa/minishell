/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 19:21:02 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cmd(t_list *cmds, int *pfds, t_list *envp, int i)
{
	int		nbr_pipes;
	char	*cmd_path;
	char	**tab;
	t_cmd	*cmd;

	cmd_path = NULL;
	tab = list_to_arr(envp);
	nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
	if (cmds->next)
		ft_dup2(pfds[i + 1], 1);
	if (i != 0)
		ft_dup2(pfds[i - 2], 0);
	close_pfds(pfds, nbr_pipes);
	cmd = cmds->content;
	if (cmd->cmd == NULL)
		exit(128);
	if (my_redirect(cmd->redir) || exec_builtin(cmd, envp, is_builtin(cmd)))
		exit(1);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
	execve(cmd_path, cmd->args, tab);
	exit(127);
}

void	my_exec(t_list *cmds, t_list *envp)
{
	int	nbr_cmds;
	int	*pfds;
	int	pid;

	pfds = NULL;
	nbr_cmds = ft_lstsize(cmds);
	if (nbr_cmds > 0)
	{
		g_exit_status = is_builtin(cmds->content);
		if (nbr_cmds == 1 && g_exit_status != 0)
			ft_builtin(cmds->content, envp, g_exit_status);
		else
		{
			ft_heredoc(cmds);
			if (nbr_cmds > 1)
				pfds = create_pipes(nbr_cmds - 1);
			pid = create_childs(cmds, pfds, envp);
			if (nbr_cmds > 1)
				close_pfds(pfds, nbr_cmds - 1);
			waitpid(pid, &g_exit_status, 0);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			wait_cmds(nbr_cmds);
		}	
	}
}
