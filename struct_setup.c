/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:26:25 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/15 17:28:12 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_size(char *command)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (command[i])
	{
		while (command[i] == ' ')
			i++;
		if (command[i] && command[i] != '"' && command[i] != 39)
		{
			while (command[i] != ' ' && command[i] != '"' && command[i] != 39
				&& command[i])
				i++;
			ret++;
		}
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"' && command[i])
				i++;
			ret++;
		}
		if (command[i] == 39)
		{
			i++;
			while (command[i] != 39 && command[i])
				i++;
			ret++;
		}
		if (command[i])
			i++;
	}
	return (ret);
}

void	allocate_array(char *s, t_cmd *cmd)
{
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_size(s);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	while (i < (ret + 1))
		cmd->args[i++] = malloc(sizeof(char) * ft_strlen(s));
	cmd->args[i] = NULL;
}

void	free_args(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}
