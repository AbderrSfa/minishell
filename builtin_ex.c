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

int	exec_cd(t_cmd *cmd, t_list *envp)
{
	char *home;
	char **pwd;
	char **oldpwd;
	t_env *env;

	pwd = NULL;
	home= NULL;
	oldpwd = NULL;
	while(envp != NULL)
	{
		env	= envp->content;
		if (ft_strncmp(env->key,"HOME",5) == 0)
			home = env->value;
		else if (ft_strncmp(env->key,"PWD",4) == 0)
			pwd = &env->value;
		else if (ft_strncmp(env->key,"OLDPWD", 7) == 0)
			oldpwd = &env->value;
		envp = envp->next;
	}
	cd(pwd, oldpwd, cmd->args[1], home);
	return (1);
}

int is_builtin(t_cmd *cmd, t_list *envp)
{
	t_env *env;
	if (ft_strncmp(cmd->cmd,"cd",3) == 0)
	{
		exec_cd(cmd, envp);
		return(1);
	}
	else if (ft_strncmp(cmd->cmd,"pwd",4) == 0)
	{
		pwd();
		return(1);
	}
	else if (ft_strncmp(cmd->cmd,"echo",5) == 0)
	{
		if (ft_strncmp(cmd->args[1],"-n", 3) == 0)
			echo(cmd->args + 2,'n');
		else
			echo(cmd->args + 1,' ');
		return(1);
	}
	else if (ft_strncmp(cmd->cmd,"env",4) == 0)
	{
		ft_env(envp);
		return(1);
	}
	else if (ft_strncmp(cmd->cmd,"exit",5) == 0)
	{
		ft_exit(g_exit_status);
	}
	else if (ft_strncmp(cmd->cmd,"unset",6) == 0)
	{
		ft_unset(envp, cmd->args[1]);
		return(1);
	}
	return (0);
}
