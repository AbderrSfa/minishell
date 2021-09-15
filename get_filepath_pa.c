/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepath_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:47:17 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/15 16:11:13 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_file_quotes(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env_lst, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
		if (redir->file == NULL)
			redir->file = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = single_quotes(s, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
	}
}

void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;
	int		j;

	j = prs->i;
	if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != '\''
		&& s[prs->i] != '>' && s[prs->i] != '<')
	{
		while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
			&& s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != '\'')
			prs->i++;
		////
		prs->outside_quote = 1;
		temp = ft_substr(s, j, prs->i - j);
		tmp = env_var_checker(temp, env_lst, prs);
		free(temp);
		temp = redir->file;
		redir->file = ft_strjoin(redir->file, tmp);
		free(tmp);
		free(temp);
		prs->outside_quote = 0;
		////
	}
}

void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	while (s[prs->i] == ' ')
		prs->i++;
	if (s[prs->i] == '$')
		if (check_ambigous_redirect(s, env_lst, prs) == -1)
			prs->ambigous = 1;
	while (s[prs->i])
	{
		join_filepath(redir, s, env_lst, prs);
		get_file_quotes(redir, s, env_lst, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}
