/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes_pa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 16:24:13 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	initialize_node(t_cmd *new, char *s)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new);
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
