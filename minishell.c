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

	sig.quit_flag = 0;
	sig.interrupt_flag = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_int);
	sig.ret = 0;
	envp = NULL;
	envp = prep_env_lst(envp, environ);
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		
/* 		printf("{%s}\n", input);
		printf("INT {%d} -- QUIT {%d}\n", sig.interrupt_flag, sig.quit_flag); */
/* 		if (input == NULL && (!sig.interrupt_flag || !sig.quit_flag))
		{
			if (!sig.interrupt_flag && !sig.quit_flag)
				ft_putstr("\b\bexit\n");
			else
				ft_putstr("exit\n");
			exit(sig.ret);
		} */
		if (input == NULL)
		{
			ft_putstr("exit\n");
			exit(sig.ret);
		}
		if (ft_strcmp(input, ""))
			add_history(input);
		temp = envp;
		if (input != NULL && !check_syntax_errors(input))
		{
			cmds = split_by_pipes(cmds, input, temp, sig.ret);
			sig.ret = my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
		sig.interrupt_flag = 0;
		sig.quit_flag = 0;
	}
	free_env_lst(envp);
	return (0);
}
