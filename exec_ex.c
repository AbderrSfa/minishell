/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/05 09:59:37 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_execve(char *path, char **args, char **tab)
{
	execve(path, args, tab);
	if (errno != 14)
		perror("minishell");
	exit(127);
}

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
	if (my_redirect(cmd->redir))
		exit (1);
	if (exec_builtin(cmd, envp, is_builtin(cmd)))
		exit(g_exit_status);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
	ft_execve(cmd_path, cmd->args, tab);
}

static void	ft_set_exit_status(int nbr_cmds)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	}
	wait_cmds(nbr_cmds);
}

int	my_exec(t_list *cmds, t_list *envp)
{
	int	nbr_cmds;
	int	*pfds;
	int	pid;

	pfds = NULL;
	nbr_cmds = ft_lstsize(cmds);
	if (ft_heredoc(cmds))
		return (1);
	if (nbr_cmds > 0)
	{
		pid = is_builtin(cmds->content);
		if (nbr_cmds == 1 && pid != 0)
			ft_builtin(cmds->content, envp, pid);
		else
		{
			if (nbr_cmds > 1)
				pfds = create_pipes(nbr_cmds - 1);
			pid = create_childs(cmds, pfds, envp);
			if (nbr_cmds > 1)
				close_pfds(pfds, nbr_cmds - 1);
			waitpid(pid, &g_exit_status, 0);
			ft_set_exit_status(nbr_cmds);
		}	
	}
	return (0);
}
