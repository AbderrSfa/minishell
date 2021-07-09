/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:54:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/09 15:57:32 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_put_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
	return (1);
}

int	check_quote_errors(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (ft_put_error("minishell: unclosed double quote error"));
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (ft_put_error("minishell: unclosed single quote error"));
		}
		i++;
	}
	return (0);
}

int	pipe_and_semi_errors(char *str)
{
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (ft_put_error
				("minishell: syntax error near unexpected token `||'"));
		else
			return (ft_put_error
				("minishell: syntax error near unexpected token `|'"));
	}
	else if (str[0] == ';')
	{
		if (str[1] == ';')
			return (ft_put_error
				("minishell: syntax error near unexpected token `;;'"));
		else
			return (ft_put_error
				("minishell: syntax error near unexpected token `;'"));
	}
	return (0);
}

int	check_syntax_errors(char *s)
{
	char	*str;

	str = ft_strtrim(s, " ");
	if (pipe_and_semi_errors(str))
	{
		free(str);
		return (1);
	}
	if (check_quote_errors(str))
	{
		free(str);
		return (1);
	}
	if (check_redir_errors(str))
	{
		free(str);
		return (1);
	}
	if (str[ft_strlen(str) - 1] == '|')
	{
		free(str);
		return (ft_put_error
			("minishell: syntax error near unexpected token `newline'"));
	}
	return (0);
}
