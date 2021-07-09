/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:54:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/09 14:51:12 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_put_error(char *error)
{
	ft_putstr(error);
	ft_putstr("\n");
	return (1);
}

int		check_quote_errors(char *s)
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
				return (ft_put_error("minishell: syntax error unclosed double quote"));
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (ft_put_error("minishell: syntax error unclosed single quote"));
		}
		i++;
	}
	return (0);
}

int		skip_quotes(char *str, int i)
{
	if (str[i] == '"')
	{
		while (str[i] && str[i] != )
	}
}

int		check_redir_errors(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
	}
}

int		check_for_trailing_pipe(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	if (str[i] == '|')
	{
		i++;
		while (str[i] == ' ')
			i++;
		if (!str[i])
			return (1);	
	}
	return (0);
}


int		check_syntax_errors(char *s)
{
	char	*str;
	int		ret;

	ret = 0;
	str = ft_strtrim(s, " ");
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (ft_put_error("minishell: syntax error near unexpected token `||'"));
		else
			return (ft_put_error("minishell: syntax error near unexpected token `|'"));
	}
	else if (str[0] == ';')
	{
		if (str[1] == ';')
			return (ft_put_error("minishell: syntax error near unexpected token `;;'"));
		else
			return (ft_put_error("minishell: syntax error near unexpected token `;'"));
	}
	if (check_for_trailing_pipe(str))
		return (ft_put_error("minishell: syntax error near unexpected token `newline'"));
	ret = check_quote_errors(str);
	//ret = check_redir_errors(str);
	return (ret);
}