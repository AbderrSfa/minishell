/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:54:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/08/30 13:25:22 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 1);
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

int	check_pipe_errors(char *s)
{
	int		i;
	int		quote;
	int		pipe;

	quote = 0;
	pipe = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			check_for_quote(s[i++], quote);
		if (s[i] == '|' && !quote)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '|')
				return (ft_put_error
					("minishell: syntax error near unexpected token `|'"));
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
	if (check_pipe_errors(str))
		return (1);
	return (0);
}

// Function is too long
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
	free(str);
	return (0);
}
