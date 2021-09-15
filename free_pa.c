/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:40:02 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/15 16:13:50 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_redirect(t_list *redir)
{
	t_list	*redir_temp;
	t_redir	*temp;

	while (redir != NULL)
	{
		redir_temp = redir;
		temp = redir->content;
		if (temp->file)
			free(temp->file);
		free(temp);
		redir = redir->next;
		free(redir_temp);
	}
}

void	free_cmds(t_list *cmd)
{
	t_list		*list_temp;
	t_cmd		*temp;
	int			i;

	i = 0;
	while (cmd != NULL)
	{
		list_temp = cmd;
		temp = cmd->content;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		if (temp->redir)
			free_redirect(temp->redir);
		free(temp);
		cmd = cmd->next;
		free(list_temp);
	}
}

void	free_env_lst(t_list *env_lst)
{
	t_env	*temp;

	while (env_lst != NULL)
	{
		temp = env_lst->content;
		free(temp->key);
		free(temp->value);
		free(env_lst->content);
		free(env_lst);
		env_lst = env_lst->next;
	}
}
