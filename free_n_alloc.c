/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:04:48 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 17:05:12 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_size(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] && s[i] != '"' && s[i] != 39)
		{
			while (s[i] != ' ' && s[i] != '"' && s[i] != 39
				&& s[i])
				i++;
			ret++;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
			ret++;
		}
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
				i++;
			ret++;
		}
		if (s[i])
			i++;
	}
	return (ret);
}

void	allocate_args(char *s, t_cmd *cmd)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	while (i < (ret + 1))
		cmd->args[i++] = malloc(sizeof(char) * ft_strlen(s));
	cmd->args[i] = NULL;
}

void	free_args(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;


	i = 0;
	while (cmd)
	{
		temp = cmd;
		if (temp->args)
		{
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		if (temp->redirect)
		{
			while (temp->redirect)
			{
				temp->redirect = cmd->redirect;
				if (temp->redirect->file)
					free(temp->redirect->file);
				free(temp->redirect);
				cmd->redirect = cmd->redirect->next;
			}
		}
		cmd = cmd->next;
		free(temp);
	}
}
