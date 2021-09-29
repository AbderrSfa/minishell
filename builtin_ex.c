/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:06:10 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 19:14:44 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (2);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (4);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (5);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (7);
	return (0);
}

static int	exec_un_ex(t_cmd *cmd, t_list *envp, int status)
{
	int	i;

	if (status == 6)
	{
		i = 1;
		while (cmd->args[i] != NULL && ft_valid_env_name(cmd->args[i]))
		{
			g_exit_status = ft_unset(envp, cmd->args[i]);
			i++;
		}
	}
	else if (status == 7)
	{
		if (cmd->args[1] == NULL)
			g_exit_status = ft_display_envp(envp);
		i = 1;
		while (cmd->args[i] != NULL && ft_valid_env_name(cmd->args[i]))
		{
			g_exit_status = ft_export(envp, cmd->args[i]);
			i++;
		}
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_list *envp, int status)
{
	static char	*gpwd;

	if (gpwd == NULL)
		gpwd = getcwd(NULL, 0);
	if (status == 1)
		g_exit_status = ft_chdir(cmd, envp, &gpwd);
	else if (status == 2)
		g_exit_status = ft_pwd(gpwd);
	else if (status == 3)
	{
		if (cmd->args[1] != NULL && ft_strncmp(cmd->args[1], "-n", 3) == 0)
			g_exit_status = ft_echo(cmd->args + 2, 'n');
		else
			g_exit_status = ft_echo(cmd->args + 1, ' ');
	}
	else if (status == 4)
		g_exit_status = ft_env(envp);
	else if (status == 5)
		ft_exit(status);
	if (status == 6 || status == 7)
		exec_un_ex(cmd, envp, status);
	return (0);
}

int	ft_builtin(t_cmd *cmd, t_list *envp, int status)
{
	int	input;
	int	output;
	int	i;

	i = 0;
	if (cmd->redir != NULL)
	{
		input = dup(0);
		output = dup(1);
		i = my_redirect(cmd->redir);
	}
	if (i == 0)
		exec_builtin(cmd, envp, status);
	if (cmd->redir != NULL)
	{
		ft_dup2(input, 1);
		ft_dup2(output, 0);
		close(input);
		close(output);
	}
	return (0);
}
