/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:47:17 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/08 16:47:43 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*temp2;
	int		j;

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
}

void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	while (s[prs->i] == ' ')
		prs->i++;
	while (s[prs->i])
	{
		join_filepath(redir, s, env_lst, prs);
		file_dbl_sgl_quote(redir, s, env_lst, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}
