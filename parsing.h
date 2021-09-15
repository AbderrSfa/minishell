/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/15 16:16:31 by asfaihi          ###   ########.fr       */
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

typedef struct s_var	t_var;
struct					s_var
{
	int					i;
	char				*result;
};

typedef struct s_prs	t_prs;
struct					s_prs
{
	int					arg_num;
	int					i;
	int					ambigous;
	int					ret_value;
	char				**extra_args;
	int					outside_quote;
};

typedef struct s_env	t_env;
struct					s_env
{
	char				*key;
	char				*value;
};

typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char				*cmd;
	char				**args;
	t_list				*redir;
};

typedef struct s_redir	t_redir;
struct					s_redir
{
	char				type;
	char				*file;
};

typedef struct s_sig	t_sig;
struct					s_sig
{
	int					quit_flag;
	int					interrupt_flag;
};

t_sig	sig;

/* Prep environment variables */
t_list	*prep_env_lst(t_list *env_lst, char **env);
t_env	*make_env_node(char *key, char *value);
char	*get_key(char *s);
char	*get_value(char *s);
char	*increment_shell_level(char *value);
void	initialize_env_node(t_env *new);

/* Check for syntax errors */
int		check_syntax_errors(char *s);
int		pipe_and_semi_errors(char *str);
int		check_pipe_errors(char *s);
int		check_for_quote(char c, int quote);
int		check_quote_errors(char *s);
int		check_redir_errors(char *str);
int		skip_quotes(char *str, int i);
int		redirection_syntax_errors(char *str, int i);
int		ft_put_error(char *error);

/* Parse simple commands */
t_list	*split_by_pipes(t_list *head, char *input, t_list *env_lst, int ret);
char	*change_pipe(char *s);
t_cmd	*new_node(char *s, t_list *env_lst, int ret);
void	initialize_prs_node(t_prs *prs, int ret);
void	initialize_cmd_node(t_cmd *new, char *s, t_list *env_lst);
void	allocate_args(char *s, t_cmd *cmd, t_list *env_lst);
int		get_size(char *s);
int		skip_space_and_redir(char *s, int i);
int		count_extra_args(char *s, int i, int j, t_list *env_lst);
int		args_counter(char *s);
void	simple_cmd_parse(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);

/* Get command args */
void	get_arg(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);
void	get_dbl_or_sgl_quotes(t_cmd *new, char *s, t_list *env_lst, t_prs *prs);
char	*double_quotes(char *s, t_list *env_lst, t_prs *prs);
char	*single_quotes(char *s, t_prs *prs);
void	is_arg_empty(t_cmd *new, char *s, t_prs *prs, int j);
void	echo_n_flag(t_cmd *new);

/* Expand environment variables */
char	*env_var_checker(char *s, t_list *env_lst, t_prs *prs);
void	check_var_edge_cases(char *s, t_var *var, t_list *env_lst, t_prs *prs);
void	get_variable(char *s, t_list *env_lst, t_var *var, t_prs *prs);
char	*variable_expander(char *key, t_list *env_lst);
char	*remove_spaces(char *s);

/* Parse redirections */
t_list	*redirections(t_list *redir, char *s, t_list *env_lst, t_prs *prs);
t_redir	*new_redirection_node(char *s, t_list *env_lst, t_prs *prs);
void	initialize_redir_node(t_redir *new);
char	get_redir_type(char first, char second);
void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);
void	get_file_quotes(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);

/* Check ambigous redirect errors */
int		check_ambigous_redirect(char *s, t_list *env_lst, t_prs *prs);
int		is_ambigous_var_valid(char *var, char *joined);
char	*get_ambigous_var(char *joined, char *var);
int		ambigous_error_message(char *expanded, char *joined, t_prs *prs, int i);

/* Free allocated memory */
void	free_cmds(t_list *cmd);
void	free_redirect(t_list *redir);
void	free_env_lst(t_list *env_lst);

/* Signal handling */
void	sig_quit(int signal);
void	sig_int(int signal);

#endif
