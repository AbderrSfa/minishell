/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:04:48 by asfaihi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/29 14:17:41 by asfaihi          ###   ########.fr       */
=======
/*   Updated: 2021/07/29 11:38:20 by asfaihi          ###   ########.fr       */
>>>>>>> 9acbd0a57dfe7dc2ca471da80e4f3f88731c1d89
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
	if ((c == '"' || c == 39) && quote == 0)
		quote = 1;
	else if ((c == '"' || c == 39) && quote == 1)
		quote = 0;
	return (quote);
}

int	get_size(char *s)
{
	int		i;
	int		quote;
	int		ret;

	i = 0;
	ret = 0;
	quote = 0;
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

void	allocate_args(char *s, t_cmd *cmd)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
<<<<<<< HEAD
	while (i <= ret)
		cmd->args[i++] = NULL;
=======
//	while (i <= ret)
//		cmd->args[i++] = NULL;
//		cmd->args[i++] = malloc(sizeof(char));
>>>>>>> 9acbd0a57dfe7dc2ca471da80e4f3f88731c1d89
}
