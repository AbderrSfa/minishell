/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 12:40:30 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_parser		t_parser;
struct						s_parser
{
	int						arg_num;
	int						i;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*key;
	char					*value;
};

typedef struct s_cmd		t_cmd;
struct						s_cmd
{
	char					*cmd;
	char					**args;
	t_list					*redirect;
};

typedef struct s_redirect	t_redirect;
struct						s_redirect
{
	char					type;
	char					*file;
};


int			get_size(char *s);
char		*change_pipe(char *s);
void		free_cmds(t_list *cmd);
void		free_env_list(t_list *env_list);
void		initialize_env_node(t_env *new);
void		allocate_args(char *s, t_cmd *cmd);
t_cmd		*new_node(char *s, t_list *env_list);
void		initialize_node(t_cmd *new, char *s);
void		env_var_parser(t_cmd *cmd, char *word);
void		initialize_redir_node(t_redirect *new);
t_env		*make_env_node(char *key, char *value);
char		*single_quotes(char *s, t_parser *parser);
char		*env_var_checker(char *s, t_list *env_list);
t_list		*prep_env_list(t_list *env_list, char **env);
t_list		*split_by_pipes(t_list *head, char *input, t_list *env_list);
char		*double_quotes(char *s, t_list *env_list, t_parser *parser);
t_redirect	*new_redirection_node(char *s, t_list *env_list, t_parser *parser);
void		get_arg(t_cmd *new, char *s, t_list *env_list, t_parser *parser);
void		get_filepath(t_redirect *redirect, char *s, t_list *env_list, t_parser * parser);
void		simple_cmd_parse(t_cmd *new, char *s, t_list *env_list, t_parser *parser);
t_list		*redirections(t_list *redirect, char *s, t_list *env_list, t_parser *parser);

#endif
