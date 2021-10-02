/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c    	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/02 19:12:22 by yabdelgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

static char	*ft_read_input(char *input, t_list *envp)
{
	input = readline("minishell-1.0$ ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_env_lst(envp);
		exit(g_exit_status);
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

	input = NULL;
	envp = prep_env_lst(NULL, environ);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_int);
		cmds = NULL;
		input = ft_read_input(input, envp);
		temp = envp;
		if (input != NULL && !check_syntax_errors(input))
		{
			cmds = split_by_pipes(cmds, input, temp);
			my_exec(cmds, envp);
		}
		free(input);
		free_cmds(cmds);
	}
	free_env_lst(envp);
	return (0);
}
