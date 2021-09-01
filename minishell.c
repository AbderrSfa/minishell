/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c    	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/07/29 11:14:46 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

// Function is too long
// Too many variables declared
int	main(void)
{
	extern char	**environ;
	char		*input;
	t_list		*cmds;
	t_list		*envp;
	t_list		*temp;
	int			ret;

	ret = 0;
	envp = NULL;
	envp = prep_env_lst(envp, environ);
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strcmp(input, ""))
			add_history(input);
		temp = envp;
		if (!check_syntax_errors(input))
		{
			cmds = split_by_pipes(cmds, input, temp, ret);
			ret = my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
	}
	free_env_lst(envp);
	return (0);
}
