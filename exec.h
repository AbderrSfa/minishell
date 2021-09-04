/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:14:01 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/29 20:21:50 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

 # include <unistd.h>
 # include <errno.h>
 # include <fcntl.h>
 # include <stdlib.h>
 # include <stdio.h>
 # include "parsing.h"
 # include "libft/libft.h"
 # include <sys/types.h>
 # include <sys/wait.h>

#define BUFFER_SIZE 1
int		my_exec(t_list *cmds, t_list *envp);

void    ft_dup2(int fd1, int fd2);
void    input_redirect(char *file);
void    output_redirect(char *file);
void    append_redirect(char *file);

char    **get_paths();
char    *get_envp(t_list *envp, char *key);
char    *get_cmd_path(char *cmd, char **paths);

void	my_redirect(t_list *redir);

void	pwd(char *gpwd);
int		ft_export(t_list *envp, char *arg);
int		ft_unset(t_list *envp, char *value);
void	ft_env(t_list *envp);
int		echo(char **argv, char option);
void	ft_exit(int status);
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_list *envp, int status);
int		cd(char **pwd, char **oldpwd, char *dir, char *home, char **gpwd);
int		exec_cd(t_cmd *cmd, t_list *envp, char **gpwd);

char	**list_to_arr(t_list *lst);
int 	ft_display_envp(t_list *envp);
int		ft_chdir(t_cmd *cmd, t_list *envp, char **path);

#endif
