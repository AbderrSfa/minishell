/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax_errors_pa.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:53:59 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/24 12:35:17 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_quotes(char *str, int i)
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

int	redirection_syntax_errors(char *str, int i)
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
				("minishell: syntax error near unexpected token `newline'", 1);
		else
		{
			ft_putstr("minishell: syntax error near unexpected token `");
			ft_putchar(str[i]);
			ft_putendl_fd("'", 1);
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
