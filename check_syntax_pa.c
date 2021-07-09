/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 12:54:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/09 15:31:06 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_put_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
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
		while (str[i] && str[i] != '"')
			i++;
	}
	if (str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

int		redirection_syntax_errors(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (!str[i])
		{
			ft_putstr("minishell: syntax error near unexpected token `newline'");
			ft_putchar('\n');
		}
		else
		{
			ft_putstr("minishell: syntax error near unexpected token `");
			ft_putchar(str[i]);
			ft_putchar('\'');	
			ft_putchar('\n');
		}
		return (-100);
	}
	return (i);
}

int		check_redir_errors(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
		while (str[i] == ' ')
			i++;
		if (str[i] == '>' || str[i] == '<')
			i = redirection_syntax_errors(str, i);
		if (i == -100)
			return (1);
		i++;
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
	if ((ret = check_quote_errors(str)))
		return (ret);
	if ((ret = check_redir_errors(str)))
		return (ret);
	if (str[ft_strlen(str) - 1] == '|')
		return (ft_put_error("minishell: syntax error near unexpected token `newline'"));
	return (ret);
}