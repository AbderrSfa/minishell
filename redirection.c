/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:39:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/23 14:43:27 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_file(t_redirect *redirect, char *s, int i)
{
	int		j;
	int		quote;

	quote = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '"' || s[i] == 39)
	{
		if (s[i] == '"')
			quote = 1;
		else
			quote = 2;
		i++;
	}
	j = i;
	if (quote == 1)
		while (s[i] && s[i] != '"')
			i++;
	else if (quote == 2)
		while (s[i] && s[i] != 39)
			i++;
	else
		while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '<')
			i++;
	redirect->file = ft_substr(s, j, i - j);
	if (quote)
		i++;
	while (s[i] == ' ')
		i++;
	return (i);
}

t_redirect	*new_redirection_node(char *s, int i, int *p2)
{
	t_redirect	*new;

	if (!(new = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	initialize_redir_node(new);
	while (s[i] == ' ')
		i++;
	if (s[i] == '>' && s[i + 1] != '>')
	{
		new->type = 'G';
		i = get_file(new, s, i + 1);
	}
	else if (s[i] == '<' && s[i + 1] != '<')
	{
		new->type = 'L';
		i = get_file(new, s, i + 1);
	}
	else if (s[i] == '>' && s[i + 1] == '>')
	{
		new->type = 'D';
		i = get_file(new, s, i + 2);
	}
	else if (s[i] == '<' && s[i + 1] == '<')
	{
		new->type = 'H';
		i = get_file(new, s, i + 2);
	}
	*p2 = i;
	return (new);
}

t_redirect	*redirections(t_redirect *redirect, char *s, int *p)
{
	int			i;
	int			*p2;
	t_redirect	*temp;

	i = 0;
	p2 = &i;
	while (s[i])
	{
		if (s[i] && s[i] != '>' && s[i] != '<')
			break;
		temp = new_redirection_node(s, i, p2);
		ft_list_add_back_redir(&redirect, temp);
	}
	*p += i;
	return (redirect);
}