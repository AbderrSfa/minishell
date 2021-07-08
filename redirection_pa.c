/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:39:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 12:41:39 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*double_quotes(char *s, t_list *env_list, t_parser *parser)
{
	int		j;
	char	*file;
	char	*temp;

	parser->i++;
	j = parser->i;
	while (s[parser->i] && s[parser->i] != '"')
		parser->i++;
	temp = ft_substr(s, j, parser->i - j);
	file = env_var_checker(temp, env_list);
	free(temp);
	parser->i++;
	return (file);
}

char	*single_quotes(char *s, t_parser *parser)
{
	int		j;
	char	*file;
	char	*temp;

	parser->i++;
	j = parser->i;
	while (s[parser->i] && s[parser->i] != 39)
		parser->i++;
	file = ft_substr(s, j, parser->i - j);
	parser->i++;
	return (file);
}

void	get_filepath(t_redirect *redirect, char *s, t_list *env_list, t_parser * parser)
{
	int		j;
	char	*temp;
	char	*temp2;

	while (s[parser->i] == ' ')
		parser->i++;
	j = parser->i;
	while (s[parser->i])
	{
		j = parser->i;
		if (s[parser->i] && s[parser->i] != '"' && s[parser->i] != 39 && s[parser->i] != '>' && s[parser->i] != '<')
		{
			while (s[parser->i] && s[parser->i] != ' ' && s[parser->i] != '<' && s[parser->i] != '>'
				&& s[parser->i] != '"' && s[parser->i] != 39)
				parser->i++;
			temp = ft_substr(s, j, parser->i - j);
			temp2 = env_var_checker(temp, env_list);
			free(temp);
			temp = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp2);
			free(temp2);
			free(temp);
		}
		if (s[parser->i] == '"')
		{
			temp = double_quotes(s, env_list, parser);
			temp2 = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp);
			free(temp);
			free(temp2);
		}
		if (s[parser->i] == 39)
		{
			temp = single_quotes(s, parser);
			temp2 = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp);
			free(temp);
			free(temp2);
		}
		if (!s[parser->i] || s[parser->i] == ' ' || s[parser->i] == '>' || s[parser->i] == '<')
			break ;
	}
	while (s[parser->i] == ' ')
		parser->i++;
}

t_redirect	*new_redirection_node(char *s, t_list *env_list, t_parser *parser)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	initialize_redir_node(new);
	while (s[parser->i] == ' ')
		parser->i++;
	if (s[parser->i] == '>' && s[parser->i + 1] != '>')
		new->type = 'G';
	else if (s[parser->i] == '<' && s[parser->i + 1] != '<')
		new->type = 'L';
	else if (s[parser->i] == '>' && s[parser->i + 1] == '>')
		new->type = 'D';
	else if (s[parser->i] == '<' && s[parser->i + 1] == '<')
		new->type = 'H';
	if (new->type == 'G' || new->type == 'L')
	{
		parser->i++;
		get_filepath(new, s, env_list, parser);
	}
	else
	{
		parser->i += 2;
		get_filepath(new, s, env_list, parser);
	}
	return (new);
}

t_list	*redirections(t_list *redirect, char *s, t_list *env_list, t_parser *parser)
{
	t_list		*new;
	t_redirect	*temp;

	while (s[parser->i])
	{
		if (s[parser->i] && s[parser->i] != '>' && s[parser->i] != '<')
			break ;
		temp = new_redirection_node(s, env_list, parser);
		new = ft_lstnew(temp);
		ft_lstadd_back(&redirect, new);
	}
	return (redirect);
}
