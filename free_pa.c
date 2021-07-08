/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:40:02 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 15:47:04 by asfaihi          ###   ########.fr       */
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
