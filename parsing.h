/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 17:38:52 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_redirect	t_redirect;
struct						s_redirect
{
	char					type;
	char					*file;
	t_redirect				*next;
};

typedef struct s_cmd		t_cmd;
struct						s_cmd
{
	char					*cmd;
	char					**args;

	int						arg_num;
	char					*env_variable;

	t_redirect				*redirect;
	t_cmd					*next;
};

int			get_size(char *s);
t_cmd		*new_node(char *s);
void		free_args(t_cmd *cmd);
char		*env_var_checker(char *s);
void		allocate_args(char *s, t_cmd *cmd);
void		initialize_node(t_cmd *new, char *s);
void		simple_cmd_parse(t_cmd *new, char *s);
void		env_var_parser(t_cmd *cmd, char *word);
void		initialize_redir_node(t_redirect *new);
char		*double_quotes(char *s, int i, int *p);
char		*single_quotes(char *s, int i, int *p);
t_cmd		*split_by_pipes(t_cmd *head, char *input);
void		ft_list_add_back(t_cmd **alst, t_cmd *new);
t_redirect	*new_redirection_node(char *s, int i, int *p);
int			get_filepath(t_redirect *redirect, char *s, int i);
t_redirect	*redirections(t_redirect *redirect, char *s, int *p);
void		ft_list_add_back_redir(t_redirect **alst, t_redirect *new);

#endif