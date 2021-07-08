/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:39:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 16:27:57 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*double_quotes(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*file;
	char	*temp;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '"')
		prs->i++;
	temp = ft_substr(s, j, prs->i - j);
	file = env_var_checker(temp, env_lst);
	free(temp);
	prs->i++;
	return (file);
}

char	*single_quotes(char *s, t_prs *prs)
{
	int		j;
	char	*file;
	char	*temp;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != 39)
		prs->i++;
	file = ft_substr(s, j, prs->i - j);
	prs->i++;
	return (file);
}

void	file_dbl_sgl_quote(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*temp2;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env_lst, prs);
		temp2 = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(temp2);
	}
	if (s[prs->i] == 39)
	{
		temp = single_quotes(s, prs);
		temp2 = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(temp2);
	}
}

void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*temp;
	char	*temp2;

	while (s[prs->i] == ' ')
		prs->i++;
	j = prs->i;
	while (s[prs->i])
	{
		j = prs->i;
		if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != 39
			&& s[prs->i] != '>' && s[prs->i] != '<')
		{
			while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
				&& s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != 39)
				prs->i++;
			temp = ft_substr(s, j, prs->i - j);
			temp2 = env_var_checker(temp, env_lst);
			free(temp);
			temp = redir->file;
			redir->file = ft_strjoin(redir->file, temp2);
			free(temp2);
			free(temp);
		}
		file_dbl_sgl_quote(redir, s, env_lst, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}

t_redir	*new_redirection_node(char *s, t_list *env_lst, t_prs *prs)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	initialize_redir_node(new);
	while (s[prs->i] == ' ')
		prs->i++;
	if (s[prs->i] == '>' && s[prs->i + 1] != '>')
		new->type = 'G';
	else if (s[prs->i] == '<' && s[prs->i + 1] != '<')
		new->type = 'L';
	else if (s[prs->i] == '>' && s[prs->i + 1] == '>')
		new->type = 'D';
	else if (s[prs->i] == '<' && s[prs->i + 1] == '<')
		new->type = 'H';
	if (new->type == 'G' || new->type == 'L')
	{
		prs->i++;
		get_filepath(new, s, env_lst, prs);
	}
	else
	{
		prs->i += 2;
		get_filepath(new, s, env_lst, prs);
	}
	return (new);
}

t_list	*redirections(t_list *redir, char *s, t_list *env_lst, t_prs *prs)
{
	t_list		*new;
	t_redir		*temp;

	while (s[prs->i])
	{
		if (s[prs->i] && s[prs->i] != '>' && s[prs->i] != '<')
			break ;
		temp = new_redirection_node(s, env_lst, prs);
		new = ft_lstnew(temp);
		ft_lstadd_back(&redir, new);
	}
	return (redir);
}
