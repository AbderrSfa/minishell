/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:52:52 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 18:04:17 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	ft_here(char *limiter)
{
	int		i;
	int		fd;
	char	*line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
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
}

void	ft_heredoc(t_list *cmds)
{
	t_cmd	*cmd;
	t_list	*red;
	t_redir	*rec;

	while (cmds)
	{
		cmd = cmds->content;
		red = cmd->redir;
		while (red != NULL)
		{
			rec = red->content;
			if (rec->type == 'H')
				ft_here(rec->file);
			red = red->next;
		}
		cmds = cmds->next;
	}
}
