/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:20:42 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/14 16:33:36 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_space_and_redir(char *s, int i)
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
	return (i);
}

int	check_for_quote(char c, int quote)
{
	if ((c == '"' || c == '\'') && quote == 0)
		quote = 1;
	else if ((c == '"' || c == '\'') && quote == 1)
		quote = 0;
	return (quote);
}

int	get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	ret = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		i = skip_space_and_redir(s, i);
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				|| (s[i] == ' ' && quote)
				|| ((s[i] == '>' || s[i] == '<') && quote))
				quote = check_for_quote(s[i++], quote);
			ret++;
		}
	}
	return (ret);
}

int		args_counter(char *s)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int		count_extra_args(char *s, t_list *env_lst)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			temp2 = variable_expander(temp, env_lst);
			if (ft_strchr(temp2, ' '))
				ret += args_counter(temp2);
		}
	}
	return (ret);
}

void	allocate_args(char *s, t_cmd *cmd, t_list *env_lst)
{
	int		ret;
	int		i;
	int		j;

	j = 0;
	ret = get_size(s);
	if (ft_strchr(s, '$'))
		ret += count_extra_args(s, env_lst);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	i = 0;
	while (i <= ret)
		cmd->args[i++] = NULL;
}
