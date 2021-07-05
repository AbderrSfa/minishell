/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/30 16:24:39 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_list_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*p;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			p = *alst;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

void	ft_list_add_back_redir(t_redirect **alst, t_redirect *new)
{
	t_redirect	*p;

	if (alst != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			p = *alst;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

void	initialize_node(t_cmd *new, char *s)
{
	int		i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->arg_num = 0;
	new->next = NULL;
	new->redirect = NULL;
	allocate_args(s, new);
}

void	initialize_redir_node(t_redirect *new)
{
	new->file = NULL;
	new->type = '\0';
	new->next = NULL;
}
