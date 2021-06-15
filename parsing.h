/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:55:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/15 17:50:14 by asfaihi          ###   ########.fr       */
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

typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char				*cmd;
	char				**args;

	int					arg_num;
	char				*env_variable;
	t_cmd				*next;
};

int		get_size(char *s);
void	free_args(t_cmd *cmd);
void	allocate_array(char *s, t_cmd *cmd);
void	env_var_parser(t_cmd *cmd, char *word);
void	simple_cmd_lexer(t_cmd *cmd, char *command);
int		double_quotes(t_cmd *cmd, char *command, int i);
int		single_quotes(t_cmd *cmd, char *command, int i);

#endif