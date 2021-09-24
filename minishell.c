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

char	*ft_read_input(char *input, t_list *envp)
{
	input = readline("minishell-1.0$ ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_env_lst(envp);
		exit(g_sig.ret);
	}
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

int	main(void)
{
	extern char	**environ;
	char		*input;
	t_list		*cmds;
	t_list		*envp;
	t_list		*temp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_int);
	envp = prep_env_lst(envp, environ);
	g_sig.ret = 0;
	while (1)
	{
		cmds = NULL;
		input = ft_read_input(input, envp);
		temp = envp;
		if (input != NULL && !check_syntax_errors(input))
		{
			cmds = split_by_pipes(cmds, input, temp, g_sig.ret);
			g_sig.ret = my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
	}
	free_env_lst(envp);
	return (0);
}
