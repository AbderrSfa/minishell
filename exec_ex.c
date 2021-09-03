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
		if (redi->type == 'O')
			output_redirect(redi->file);
		if (redi->type == 'A')
			append_redirect(redi->file);
		if (redi->type == 'I')
			input_redirect(redi->file);
//		if (redi->type == 'H')
//			here_redirect(redi->file);
		redir = redir->next;
	}
}

void    exec_cmd(t_list *cmds, int *pfds, t_list *envp, int i)
{
    int		j;
    int		nbr_pipes;
	char	*cmd_path = NULL;
	t_cmd	*cmd;
	char **tab;
		

	tab = list_to_arr(envp);
    nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
    if (cmds->next)
        ft_dup2(pfds[i + 1], 1);
    if (i != 0)
        ft_dup2(pfds[i - 2], 0);
    close_pfds(pfds, nbr_pipes);
	cmd = cmds->content;
	if(cmd->cmd == NULL)
		exit(128);
	my_redirect(cmd->redir);
	if (exec_builtin(cmd, envp, is_builtin(cmd)))
		exit(0);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
    execve(cmd_path, cmd->args, tab);
    exit(127);
}

void    here_docs(t_list *cmds)
{
	t_cmd		*cmd;

    while (cmds)
    {
		cmd = cmds->content;
		if (cmd->redir != NULL)
			here_doc(cmd->redir, 0);
        cmds = cmds->next;
    }
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
	return (pid);
}

int builtin(t_cmd *cmd, t_list *envp, int status)
{
	int input;
	int output;
	
	if (cmd->redir != NULL)
	{
		input = dup(0);
		output = dup(1);
		my_redirect(cmd->redir);
	}
	exec_builtin(cmd, envp, status);
	if (cmd->redir != NULL)
	{
		ft_dup2(input, 1);
		ft_dup2(output,0);
		close(input);
		close(output);
	}
	return (0);
}

int my_exec(t_list *cmds, t_list *envp)
{
	int		nbr_cmds;
	int		*pfds;
	char	*cmd;
	int		pid;
	int		status;

	nbr_cmds = ft_lstsize(cmds);
	if (nbr_cmds < 1)
		return (0);
	status = is_builtin(cmds->content);
	if (nbr_cmds == 1 && status != 0)
		status = builtin(cmds->content, envp, status);
	else
	{
	//	here_docs(cmds);
		if (nbr_cmds > 1)
			pfds = create_pipes(nbr_cmds - 1);
		pid = create_childs(cmds, pfds, envp);
		if (nbr_cmds > 1)
			close_pfds(pfds, nbr_cmds - 1);
		waitpid(pid,&status,0);
		if ( WIFEXITED(status) )
        	status = WEXITSTATUS(status);        
		wait_cmds(nbr_cmds);
	}	
	return (status);
}
