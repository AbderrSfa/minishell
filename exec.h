/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:14:01 by yabdelgh          #+#    #+#             */
/*   Updated: 2021/07/19 13:15:38 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

 # include <unistd.h>
 # include <errno.h>
 # include <fcntl.h>
 # include <stdlib.h>
 # include <stdio.h>
#include "parsing.h"

void my_exec(t_list *cmds, t_list *envp);

void    ft_dup2(int fd1, int fd2);
void    input_redirect(char *file);
void    output_redirect(char *file);
void    append_redirect(char *file);
#endif
