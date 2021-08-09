/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepath_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:47:17 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/29 15:52:28 by asfaihi          ###   ########.fr       */
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
		if (redir->file == NULL)
			redir->file = ft_strdup("");
	}
	if (s[prs->i] == '\'')
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
	if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != '\''
		&& s[prs->i] != '>' && s[prs->i] != '<')
	{
		while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
			&& s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != '\'')
			prs->i++;
		temp = ft_substr(s, j, prs->i - j);
		temp2 = env_var_checker(temp, env_lst, prs);
		free(temp);
		temp = redir->file;
		redir->file = ft_strjoin(redir->file, temp2);
		free(temp2);
		free(temp);
	}
}

int	check_ambigous_redirect(char *s, t_list *env_lst, t_prs *prs)
{
	char	*var;
	char	*temp;
	char	*expanded;
	char	*joined;
	int		i;
	int		j;

	var = NULL;
	temp  = NULL;
	expanded = NULL;
	joined = NULL;
	i = prs->i;
	while (!expanded && s[i] == '$')
	{
		i++;
		j = i;
		while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '<' && s[i] != '$')
			i++;
		var = ft_substr(s, j, i - j);
		if (ft_strchr(var, '"') || ft_strchr(var, '\''))
		{
			free(var);
			free(joined);
			return (0);
		}
		temp = joined;
		joined = ft_strjoin(joined, "$");
		free(temp);
		joined = ft_strjoin(joined, var);
		expanded = variable_expander(var, env_lst);
		free(var);
	}
	if (!expanded)
	{
		ft_putstr("minishell: ");
		ft_putstr(joined);
		ft_put_error(": ambiguous redirect");
		free(joined);
		prs->i = i;
		return (-1);
	}
	free(joined);
	free(expanded);
	return (0);
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
		file_dbl_sgl_quote(redir, s, env_lst, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}
