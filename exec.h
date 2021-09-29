/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdelgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:14:01 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/09/29 18:00:53 by yabdelgh         ###   ########.fr       */
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

//	exec_ex.c
void	my_exec(t_list *cmds, t_list *envp);

// redirection_ex.c
void    ft_dup2(int fd1, int fd2);
void	my_redirect(t_list *redir);
int		input_redirect(char *file);
int		output_redirect(char *file);
int		append_redirect(char *file);


void	ft_heredoc(t_list *cmds);
char    **get_paths();
char    *get_envp(t_list *envp, char *key);
char    *get_cmd_path(char *cmd, char **paths);


int		ft_export(t_list *envp, char *arg);
int		ft_unset(t_list *envp, char *value);
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_list *envp, int status);

char	**list_to_arr(t_list *lst);
int 	ft_display_envp(t_list *envp);

// chdir_ex.c
int		ft_chdir(t_cmd *cmd, t_list *envp, char **path);

// builins_ex.c
int ft_echo (char **argv, char option);
int ft_env(t_list *envp);
int ft_pwd(char *gpwd);

void ft_exit(int status);

// builtin_ex.c
int ft_builtin(t_cmd *cmd, t_list *envp, int status);

// cmd_ex.c
void	wait_cmds(int nbr_cmds);
void	close_pfds(int *pfds, int nbr);

int		*create_pipes(int nbr_pipes);
int		create_childs(t_list *cmds, int *pfds, t_list *envp);

// exec_ex.c
void exec_cmd(t_list *cmds, int *pfds, t_list *envp, int i);

// unset_ex.c
int ft_unset(t_list *envp, char *value);
int ft_export(t_list *envp, char *arg);
int	ft_valid_env_name(char *value);

#endif
