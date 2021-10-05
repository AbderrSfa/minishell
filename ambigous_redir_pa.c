/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous_redir_pa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:44:31 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 14:27:43 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_ambigous_var_valid(char *var, char *joined)
{
	if (ft_strchr(var, '"') || ft_strchr(var, '\''))
	{
		free(var);
		free(joined);
		return (0);
	}
	return (1);
}

static int	ambigous_err_msg(char *expanded, char *joined, t_prs *prs, int i)
{
	if (!expanded || ft_strchr(expanded, ' '))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(joined, 2);
		ft_put_error(": ambiguous redirect");
		free(joined);
		prs->i = i;
		return (-1);
	}
	free(joined);
	free(expanded);
	return (0);
}

static char	*get_ambigous_var(char *joined, char *var)
{
	char	*temp;

	temp = NULL;
	temp = joined;
	joined = ft_strjoin(joined, "$");
	free(temp);
	temp = joined;
	joined = ft_strjoin(joined, var);
	free(temp);
	return (joined);
}

static int	find_end_of_var(char *s, int i)
{
	if (ft_isdigit(s[i]))
		i++;
	else
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	return (i);
}

int	check_ambigous_redirect(char *s, t_list *env_lst, t_prs *prs)
{
	char	*var;
	char	*expanded;
	char	*joined;
	int		i;
	int		j;

	expanded = NULL;
	joined = NULL;
	i = prs->i;
	while (!expanded && s[i] == '$')
	{
		i++;
		j = i;
		i = find_end_of_var(s, i);
		var = ft_substr(s, j, i - j);
		if (!is_ambigous_var_valid(var, joined))
			return (0);
		joined = get_ambigous_var(joined, var);
		expanded = variable_expander(var, env_lst);
		free(var);
	}
	if (!ambigous_err_msg(expanded, joined, prs, i))
		return (0);
	return (-1);
}
