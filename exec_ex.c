/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:06:42 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/14 15:18:24 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
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
		if (redi->type == 'D')
			output_redirect(redi->file);
		if (redi->type == 'D')
			append_redirect(redi->file);
		redir = redir->next;
	}
}
void    exec_cmd(t_list *cmds, int *pfds, int i)
{
    int j;
    int nbr_pipes;
	t_cmd *cmd;

    nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
    if (cmds->next)
        ft_dup2(pfds[i + 1], 1);
    if (i != 0 )
        ft_dup2(pfds[i - 2], 0);
	cmd = cmds->content;
	my_redirect(cmd->redir);
    close_pfds(pfds, nbr_pipes);
    execve(cmd->cmd, cmd->args, NULL);
    perror("execve: ");
    exit(0);
}

void    create_childs(t_list *cmds, int *pfds)
{
    int         i;
    int         pid;

    i = 0;
    while (cmds)
    {
        pid = fork();
        if (pid == 0)
            exec_cmd(cmds, pfds, i);
        cmds = cmds->next;
        i += 2;
    }
}

void my_exec(t_list *cmds, t_list *envp)
{
	int		nbr_pipes;
	int		*pfds;

	nbr_pipes = ft_lstsize(envp);
	pfds = create_pipes(nbr_pipes);
	create_childs(cmds, pfds);
	close_pfds(pfds, nbr_pipes);
	wait_cmds(nbr_pipes + 1);
}
