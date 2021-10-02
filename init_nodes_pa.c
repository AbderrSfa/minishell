/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes_pa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 14:25:12 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	initialize_cmd_node(t_cmd *new, char *s, t_list *env_lst)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env_lst);
}

void	initialize_redir_node(t_redir *new)
{
	new->file = NULL;
	new->type = '\0';
}

void	initialize_env_node(t_env *new)
{
	new->key = NULL;
	new->value = NULL;
}

void	initialize_prs_node(t_prs *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambigous = 0;
	prs->ret_value = g_exit_status;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}
