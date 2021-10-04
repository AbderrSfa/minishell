/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_errors_pa.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:53:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 12:24:11 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	skip_quotes(char *str, int i)
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

static int	redirection_syntax_errors(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		i += 2;
	else
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		if (!str[i])
			ft_putendl_fd
				("minishell: syntax error near unexpected token `newline'", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("'", 2);
		}
		return (-100);
	}
	return (i);
}

int	check_redir_errors(char *str)
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
