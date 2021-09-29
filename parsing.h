/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 14:08:44 by asfaihi          ###   ########.fr       */
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
	int						ambigous;
	int						ret_value;
	char					**extra_args;
	int						outside_quote;
	t_var					var;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*key;
	char					*value;
};

typedef struct s_redir		t_redir;
struct						s_redir
{
	char					type;
	char					*file;
};

typedef struct s_cmd		t_cmd;
struct						s_cmd
{
	char					*cmd;
	char					**args;
	t_list					*redir;
};

int							g_exit_status;

/* Prep environment variables */
t_list	*prep_env_lst(t_list *env_lst, char **env);
void	initialize_env_node(t_env *new);
t_env	*make_env_node(char *key, char *value);
char	*get_value(char *s);
char	*get_key(char *s);

/* Check for syntax errors */
int		check_syntax_errors(char *s);
int		check_for_quote(char c, int quote);
int		check_redir_errors(char *str);
int		ft_put_error(char *error);

/* Parse simple commands */
t_list	*split_by_pipes(t_list *head, char *input, t_list *env_lst);
t_cmd	*new_node(char *s, t_list *env_lst);
void	initialize_prs_node(t_prs *prs);
void	initialize_cmd_node(t_cmd *new, char *s, t_list *env_lst);
void	allocate_args(char *s, t_cmd *cmd, t_list *env_lst);
int		get_size(char *s);
int		count_extra_args(char *s, int i, int j, t_list *env_lst);

/* Get command args */
void	fill_arg(char *temp, t_cmd *new, t_list *env_lst, t_prs *prs);
void	add_extra_args(t_cmd *new, t_prs *prs);
char	*double_quotes(char *s, t_list *env_lst, t_prs *prs);
char	*single_quotes(char *s, t_prs *prs);
void	echo_n_flag(t_cmd *new);

/* Expand environment variables */
char	*env_var_checker(char *s, t_list *env_lst, t_prs *prs);
char	*variable_expander(char *key, t_list *env_lst);
char	*remove_spaces(char *s);

/* Parse redirections */
t_list	*redirections(t_list *redir, char *s, t_list *env_lst, t_prs *prs);
void	initialize_redir_node(t_redir *new);
void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs);

/* Check ambigous redirect errors */
int		check_ambigous_redirect(char *s, t_list *env_lst, t_prs *prs);

/* Free allocated memory */
void	free_cmds(t_list *cmd);
void	free_env_lst(t_list *env_lst);

/* Signal handling */
void	sig_int(void);

#endif
