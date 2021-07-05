/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 14:50:52 by asfaihi          ###   ########.fr       */
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

	t_redirect				*redirect;
	t_cmd					*next;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*key;
	char					*value;
	t_env					*next;
};

/* typedef struct s_env		t_env;
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
	int						arg_num;
	t_list					*redirect;
};

typedef struct s_redirect	t_redirect;
struct						s_redirect
{
	char					type;
	char					*file;
}; */


int			get_size(char *s);
t_cmd		*new_node(char *s, t_env *env_list);
void		free_cmds(t_cmd *cmd);
char		*change_pipe(char *s);
char		*env_var_checker(char *s, t_env *env_list);
void		free_env_list(t_env *env_list);
void		initialize_env_node(t_env *new);
void		allocate_args(char *s, t_cmd *cmd);
void		initialize_node(t_cmd *new, char *s);
void		simple_cmd_parse(t_cmd *new, char *s, t_env *env_list);
void		env_var_parser(t_cmd *cmd, char *word);
void		initialize_redir_node(t_redirect *new);
char		*double_quotes(char *s, int i, int *p, t_env *env_list);
char		*single_quotes(char *s, int i, int *p);
t_env		*make_env_node(char *key, char *value);
t_cmd		*split_by_pipes(t_cmd *head, char *input, t_env *env_list);
void		ft_list_add_back(t_cmd **alst, t_cmd *new);
t_env		*prep_env_list(t_env *env_list, char **env);
t_redirect	*new_redirection_node(char *s, int i, int *p, t_env *env_list);
void		ft_list_add_back_env(t_env **alst, t_env *new);
int			get_filepath(t_redirect *redirect, char *s, int i, t_env *env_list);
t_redirect	*redirections(t_redirect *redirect, char *s, int *p, t_env *env_list);
void		ft_list_add_back_redir(t_redirect **alst, t_redirect *new);

#endif
