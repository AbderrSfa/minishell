/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 10:59:18 by asfaihi          ###   ########.fr       */
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
	int		i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd)
		free(cmd);
}

void	initialize_node(t_cmd *new, char *s)
{
	new->cmd = NULL;
	new->args = NULL;
	new->arg_num = 0;
	new->env_variable = NULL;
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