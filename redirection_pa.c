/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:39:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/06 15:18:55 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*double_quotes(char *s, int i, int *p, t_list *env_list)
{
	int		j;
	char	*file;
	char	*temp;

	j = i;
	while (s[i] && s[i] != '"')
		i++;
	temp = ft_substr(s, j, i - j);
	file = env_var_checker(temp, env_list);
	free(temp);
	i++;
	*p = i;
	return (file);
}

char	*single_quotes(char *s, int i, int *p)
{
	int		j;
	char	*file;
	char	*temp;

	j = i;
	while (s[i] && s[i] != 39)
		i++;
	file = ft_substr(s, j, i - j);
	i++;
	*p = i;
	return (file);
}

int	get_filepath(t_redirect *redirect, char *s, int i, t_list *env_list)
{
	int		j;
	int		*p;
	char	*temp;
	char	*temp2;

	p = &i;
	while (s[i] == ' ')
		i++;
	j = i;
	while (s[i])
	{
		j = i;
		if (s[i] && s[i] != '"' && s[i] != 39 && s[i] != '>' && s[i] != '<')
		{
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>'
				&& s[i] != '"' && s[i] != 39)
				i++;
			temp = ft_substr(s, j, i - j);
			temp2 = env_var_checker(temp, env_list);
			free(temp);
			temp = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp2);
			free(temp2);
			free(temp);
		}
		if (s[i] == '"')
		{
			temp = double_quotes(s, i + 1, p, env_list);
			temp2 = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp);
			free(temp);
			free(temp2);
		}
		if (s[i] == 39)
		{
			temp = single_quotes(s, i + 1, p);
			temp2 = redirect->file;
			redirect->file = ft_strjoin(redirect->file, temp);
			free(temp);
			free(temp2);
		}
		if (!s[i] || s[i] == ' ' || s[i] == '>' || s[i] == '<')
			break ;
	}
	while (s[i] == ' ')
		i++;
	return (i);
}

t_redirect	*new_redirection_node(char *s, int i, int *p2, t_list *env_list)
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
		i = get_filepath(new, s, i + 1, env_list);
	else
		i = get_filepath(new, s, i + 2, env_list);
	*p2 = i;
	return (new);
}

t_list	*redirections(t_list *redirect, char *s, int *p, t_list *env_list)
{
	int			i;
	int			*p2;
	t_list		*new;
	t_redirect	*temp;

	i = 0;
	p2 = &i;
	while (s[i])
	{
		if (s[i] && s[i] != '>' && s[i] != '<')
			break ;
		temp = new_redirection_node(s, i, p2, env_list);
		new = ft_lstnew(temp);
		ft_lstadd_back(&redirect, new);
	}
	*p += i;
	return (redirect);
}
