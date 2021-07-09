/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/09 14:16:29 by asfaihi          ###   ########.fr       */
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

# define GREEN	"\033[1;32m"
# define RED	"\033[0;31m"
# define WHITE	"\033[0m"
# define BLUE "\033[0;34m"

typedef struct s_var		t_var;
struct						s_var
{
	int						i;
	char					*result;
};

typedef struct s_prs		t_prs;
struct						s_prs
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
	t_list					*redir;
};

typedef struct s_redir		t_redir;
struct						s_redir
{
	char					type;
	char					*file;
};



char		*get_key(char *s);
int			get_size(char *s);
char		*get_value(char *s);
char		*change_pipe(char *s);
void		free_cmds(t_list *cmd);
int			ft_put_error(char *error);
int			check_syntax_errors(char *s);
void		free_redirect(t_list *redir);
void		free_env_lst(t_list *env_lst);
void		initialize_env_node(t_env *new);
int			check_for_quote(char c, int quote);
void		allocate_args(char *s, t_cmd *cmd);
t_cmd		*new_node(char *s, t_list *env_lst);
void		env_var_prs(t_cmd *cmd, char *word);
void		initialize_redir_node(t_redir *new);
char		*single_quotes(char *s, t_prs *prs);
int			skip_space_and_redir(char *s, int i);
void		initialize_node(t_cmd *new, char *s);
t_env		*make_env_node(char *key, char *value);
char		get_redir_type(char first, char second);
char		*env_var_checker(char *s, t_list *env_lst);
t_list		*prep_env_lst(t_list *env_lst, char **env);
char		*variable_expander(char *key, t_list *env_lst);
void		get_variable(char *s, t_list *env_lst, t_var *var);
char		*double_quotes(char *s, t_list *env_lst, t_prs *prs);
void		get_arg(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);
t_list		*split_by_pipes(t_list *head, char *input, t_list *env_lst);
t_redir		*new_redirection_node(char *s, t_list *env_lst, t_prs *prs);
void		get_file(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
void		get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
void		simple_cmd_parse(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);
t_list		*redirections(t_list *redir, char *s, t_list *env_lst, t_prs *prs);
void		join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
void		get_dbl_and_sgl_quotes(t_cmd *new, char *s, t_list *env_lst,
				t_prs *prs);
void		file_dbl_sgl_quote(t_redir *redir, char *s, t_list *env_lst,
				t_prs *prs);

#endif
