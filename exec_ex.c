/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 19:54:21 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int *create_pipes(int nbr_pipes)
{
    int *pfds;
    int i;
    int j;

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

void    close_pfds(int *pfds, int nbr)
{
    int i;

    i = 0;
    while (i < 2 * nbr)
    {
        close(pfds[i]);
        i++;
    }
}

void    wait_cmds(int nbr_cmds)
{
    int i;

    i = 0;
    while (i < nbr_cmds)
    {
        wait(NULL);
        i++;
    }
}

void my_redirect(t_list *redir)
{
	t_redir *redi;

	while (redir != NULL)
	{
		redi = redir->content;
		if (redi->type == 'G')
			output_redirect(redi->file);
		if (redi->type == 'D')
			append_redirect(redi->file);
		redir = redir->next;
	}
}

void    exec_cmd(t_list *cmds, int *pfds, t_list *envp, int i)
{
    int		j;
    int		nbr_pipes;
	char	*cmd_path = NULL;
	t_cmd	*cmd;

    nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
    if (cmds->next)
        ft_dup2(pfds[i + 1], 1);
    if (i != 0 )
        ft_dup2(pfds[i - 2], 0);
	cmd = cmds->content;
	my_redirect(cmd->redir);
    close_pfds(pfds, nbr_pipes);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
	if (is_builtin(cmd, envp))
		exit(0);
    execve(cmd_path, cmd->args, g_env);
   // perror("execve: ");
    exit(127);
}

int    create_childs(t_list *cmds, int *pfds, t_list *envp)
{
    int         i;
    int         pid;

    i = 0;
    while (cmds)
    {
        pid = fork();
        if (pid == 0)
            exec_cmd(cmds, pfds,envp, i);
        cmds = cmds->next;
        i += 2;
    }
	return (pid);//
}

int my_exec(t_list *cmds, t_list *envp)
{
	int		nbr_cmds;
	int		*pfds;
	char	*cmd;
	int		pid;
	int		status;

	nbr_cmds = ft_lstsize(cmds);
	if (nbr_cmds < 2 && is_builtin(cmds->content, envp))
		return(0);
	if (nbr_cmds > 1)//
		pfds = create_pipes(nbr_cmds - 1);
	pid = create_childs(cmds, pfds, envp);
	if (nbr_cmds > 1)//
		close_pfds(pfds, nbr_cmds - 1);
	waitpid(pid,&status,0);//
	if ( WIFEXITED(status) )
    {
        g_exit_status = WEXITSTATUS(status);        
        printf("Exit status of the child was %d\n", 
                                     g_exit_status);
    }
	wait_cmds(nbr_cmds);
	return(0);
}
