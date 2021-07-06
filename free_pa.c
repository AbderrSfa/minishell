/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_alloc_pa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:04:48 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/06 14:56:01 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_redirect(t_list *redir)
{
	t_redirect	*temp;

	while (redir != NULL)
	{
		temp = redir->content;
		if (temp->file)
			free(temp->file);
		free(temp);
		free(redir);
		redir = redir->next;
	}
}

void	free_cmds(t_list *cmd)
{
	t_cmd		*temp;
	t_list		*redir;
	int			i;

	i = 0;
	while (cmd != NULL)
	{
		temp = cmd->content;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		if (temp->redirect)
			free_redirect(temp->redirect);
		free(temp);
		free(cmd);
		cmd = cmd->next;
	}
}

void	free_env_list(t_list *env_list)
{
	t_env	*temp;

	while (env_list != NULL)
	{
		temp = env_list->content;
		free(temp->key);
		free(temp->value);
		free(env_list->content);
		free(env_list);
		env_list = env_list->next;
	}
}
