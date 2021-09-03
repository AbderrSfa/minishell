/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:31:14 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/03 12:21:30 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	extern char **environ;
	int		i;
	char	*input;
	t_list	*cmds;
	t_list	*templ;
	t_cmd	*temp3;

	t_list	*env_lst;
	t_list	*temp;

	t_list	*tempredir;
	t_redir	*tempredir2;
	int		ret;

	sig.quit_flag = 0;
	sig.interrupt_flag = 0;
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	ret = 0;
	env_lst = NULL;
	env_lst = prep_env_lst(env_lst, environ);
	while (1)
	{
		cmds = NULL;
		input = readline("minishell-1.0$ ");
		if (ft_strcmp(input, ""))
			add_history(input);
		temp = env_lst;
		if (input != NULL && !check_syntax_errors(input))
			cmds = split_by_pipes(cmds, input, temp, ret);
		free(input);
		i = 0;
		int		j;
		int		k;
		j = 1;
		k = 1;
		templ = cmds;
		while (templ != NULL)
		{
			temp3 = templ->content;
			printf("\033[0;35m****************** Simple command %d ******************\033[0;0m\n", j++);
			i = 0;
			while (temp3->args[i])
			{
				if (i == 0)
					printf("\033[0;33mCommand:\033[0;0m %s\n", temp3->cmd);
				printf("Arg: %s\n", temp3->args[i++]);
			}
			while (temp3->redir != NULL)
			{
				tempredir = temp3->redir;
				tempredir2 = tempredir->content;
				printf("\033[0;36m********* Redirection %d *********\033[0;0m\n", k++);
				printf("\033[0;37mType:\033[0;0m %c\n", tempredir2->type);
				printf("\033[0;38mFile:\033[0;0m %s\n", tempredir2->file);
				temp3->redir = temp3->redir->next;
			}
			templ = templ->next;
		}
		free_cmds(cmds);
		sig.quit_flag = 0;
		sig.interrupt_flag = 0;
	}
	free_env_lst(env_lst);
	return (0);
}