/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:33:00 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 14:53:30 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
void	ft_dup2(int fd1, int fd2)
{
	int	i;

	i = dup2(fd1, fd2);
	if (i < 0)
	{
		perror("dup2");
		exit(0);
	}
}

void	input_redirect(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(0);
	}
	ft_dup2(fd, 0);
	close(fd);
}

void	output_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror(file);
		exit(0);
	}
	ft_dup2(fd, 1);
	close(fd);
}

void	append_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		perror(file);
		exit(0);
	}
	ft_dup2(fd, 1);
	close(fd);
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
		if (redi->type == 'H')
			input_redirect("/tmp/file1");
		redir = redir->next;
	}
}
