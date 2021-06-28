/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:39:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/28 17:21:19 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*double_quotes(char *s, int i, int *p)
{
	int		j;
	char	*file;

	j = i;
	while (s[i] && s[i] != '"')
		i++;
	if (s[i] != '"')
	{
		printf("Unclosed double quote");
		exit(EXIT_FAILURE);
	}
	file = ft_substr(s, j, i - j);
	file = env_var_checker(file);
	i++;
	*p = i;
	return (file);
}

char	*single_quotes(char *s, int i, int *p)
{
	int		j;
	char	*file;

	j = i;
	while (s[i] && s[i] != 39)
		i++;
	if (s[i] != 39)
	{
		printf("Unclosed single quote");
		exit(EXIT_FAILURE);
	}
	file = ft_substr(s, j, i - j);
	i++;
	*p = i;
	return (file);
}

int	get_filepath(t_redirect *redirect, char *s, int i)
{
	int		j;
	int		*p;
	char	*temp;

	p = &i;
	while (s[i] == ' ')
		i++;
	j = i;
	while (s[i])
	{
		if (s[i] && s[i] != '"' && s[i] != 39 && s[i] != '>' && s[i] != '<')
		{
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>'
				&& s[i] != '"' && s[i] != 39)
				i++;
			redirect->file = env_var_checker(temp = ft_substr(s, j, i - j));
		}
		if (s[i] == '"')
			redirect->file = ft_strjoin(redirect->file,
					temp = double_quotes(s, i + 1, p));
		if (s[i] == 39)
			redirect->file = ft_strjoin(redirect->file,
					temp = single_quotes(s, i + 1, p));
		if (!s[i] || s[i] == ' ' || s[i] == '>' || s[i] == '<')
			break ;
	}
	while (s[i] == ' ')
		i++;
	return (i);
}

t_redirect	*new_redirection_node(char *s, int i, int *p2)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	initialize_redir_node(new);
	while (s[i] == ' ')
		i++;
	if (s[i] == '>' && s[i + 1] != '>')
		new->type = 'G';
	else if (s[i] == '<' && s[i + 1] != '<')
		new->type = 'L';
	else if (s[i] == '>' && s[i + 1] == '>')
		new->type = 'D';
	else if (s[i] == '<' && s[i + 1] == '<')
		new->type = 'H';
	if (new->type == 'G' || new->type == 'L')
		i = get_filepath(new, s, i + 1);
	else
		i = get_filepath(new, s, i + 2);
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
			break ;
		temp = new_redirection_node(s, i, p2);
		ft_list_add_back_redir(&redirect, temp);
	}
	*p += i;
	return (redirect);
}
