/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:33:00 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/13 17:54:01 by yabdelgh         ###   ########.fr       */
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

void	here_redirect(char *limiter)
{
	int	fd;
	char *file;

	file = ft_strjoin("/tmp/.!#$@%6^m.5*(,@~0-(qH)9]|",limiter);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(0);
	}
	ft_dup2(fd, 0);
	close(fd);
}

int heredoc(char *limiter, int input)
{
    int i;
    int fd;
    char *line;
	char *file;

	file = ft_strjoin("/tmp/.!#$@%6^m.5*(,@~0-(qH)9]|",limiter);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    while (1)
    {
        write(input,">",1);
        i = get_next_line(input, &line);
        i = ft_memcmp(line, limiter, ft_strlen(limiter) + 1);
        if (i == 0)
        {
            free(line);
            close(fd);
            return (0);
        }
        write(fd, line, ft_strlen(line));
        free(line);
        write(fd, "\n", 1);
    }
}

void here_doc(t_list *redir, int input)
{   
    t_redir *redi;
    while (redir != NULL)
    {
        redi = redir->content;
        if (redi->type == 'H')
            heredoc(redi->file, input);
        redir = redir->next;
    }
    close(input);
}

