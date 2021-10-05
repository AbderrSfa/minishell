/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:52:52 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/10/05 10:33:07 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_here_sig(int signal)
{
	exit(1);
}

static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

static void	ft_here(char *limiter)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_here_sig);
		line = readline(">");
		i = strncmp(line, limiter, ft_strlen(limiter) + 1);
		if (i == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

static int	ft_exec_heredoc(t_redir *rec)
{
	int		pid;	

	pid = fork();
	if (pid == 0)
		ft_here(rec->file);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}

int	ft_heredoc(t_list *cmds)
{
	t_cmd	*cmd;
	t_list	*red;
	t_redir	*rec;

	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	while (cmds)
	{
		cmd = cmds->content;
		red = cmd->redir;
		while (red != NULL)
		{
			rec = red->content;
			if (rec->type == 'H')
			{
				if (ft_exec_heredoc(rec) == 1)
					return (1);
			}
			red = red->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
