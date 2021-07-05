/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:04:48 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/05 12:02:10 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	i = 0;
	ret = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		while (s[i] == '>' || s[i] == '<')
		{
			i++;
			while (s[i] == ' ')
				i++;
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				i++;
		}
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>') || (s[i] == ' ' && quote)
				|| ((s[i] == '>' || s[i] == '<') && quote))
			{
				if ((s[i] == '"' || s[i] == 39) && quote == 0)
					quote = 1;
				else if ((s[i] == '"' || s[i] == 39) && quote == 1)
					quote = 0;
				i++;
			}
			ret++;
		}
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
	while (i < ret)
		cmd->args[i++] = malloc(sizeof(char) * ft_strlen(s));
	cmd->args[i] = NULL;
}

void	free_cmds(t_cmd *cmd)
{
	int		i;


	i = 0;
	while (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->redirect)
		{
			while (cmd->redirect)
			{
				cmd->redirect = cmd->redirect;
				if (cmd->redirect->file)
					free(cmd->redirect->file);
				free(cmd->redirect);
				cmd->redirect = cmd->redirect->next;
			}
		}
		free(cmd);
		cmd = cmd->next;
	}
}
