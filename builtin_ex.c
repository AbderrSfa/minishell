/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:06:10 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 20:04:27 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_builtin(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(cmd->cmd,"cd",3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd,"pwd",4) == 0)
		return (2);
	else if (ft_strncmp(cmd->cmd,"echo",5) == 0)
		return (3);
	else if (ft_strncmp(cmd->cmd,"env",4) == 0)
		return (4);
	else if (ft_strncmp(cmd->cmd,"exit",5) == 0)
		return (5);
	else if (ft_strncmp(cmd->cmd,"unset",6) == 0)
		return (6);
	else if (ft_strncmp(cmd->cmd,"export",7) == 0)
		return (7);
	return (0);
}

int exec_builtin(t_cmd *cmd, t_list *envp, int status)
{
	int i;
	t_env *env;
	static char *gpwd;

	if (gpwd == NULL)
		gpwd = getcwd(NULL,0);	
	if (status == 1)
	{
		ft_chdir(cmd, envp, &gpwd);
		return(1);
	}
	else if (status == 2)
	{
		pwd(gpwd);
		return(1);
	}
	else if (status == 3)
	{
		if ( cmd->args[1] != NULL && ft_strncmp(cmd->args[1],"-n", 3) == 0)
			echo(cmd->args + 2,'n');
		else
			echo(cmd->args + 1,' ');
		return(1);
	}
	else if (status == 4)
	{
		ft_env(envp);
		return(1);
	}
	else if (status == 5)
	{
		ft_exit(status);
	}
	else if (status == 6)
	{
		i = 1;
		while(cmd->args[i] != NULL)
		{
			ft_unset(envp, cmd->args[i]);
			i++;
		}
		return(1);
	}
	else if (status == 7)
	{
		i = 1;
		if(cmd->args[1] == NULL)
		{
			ft_display_envp(envp);
			return (1);
		}
		while(cmd->args[i] != NULL)
		{
			ft_export(envp, cmd->args[i]);
			i++;
		}
		return(1);
	}
	return (0);
}

