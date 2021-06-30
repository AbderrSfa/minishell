/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:26:06 by asfaihi           #+#    #+#             */
/*   Updated: 2021/06/30 16:33:20 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Ignore this main

int	main(void)
{
	int	i;
	int	j;
	int	k;
	t_cmd	*templ;

	i = 0;	
	j = 1;
	k = 1;
	program_loop();
	while (templ != NULL)
	{
		printf("\033[0;35m****************** Simple command %d ******************\033[0;0m\n", j++);
		i = 0;
		while (i < templ->arg_num)
		{
			if (i == 0)
				printf("\033[0;33mCommand:\033[0;0m %s\n", templ->cmd);
			printf("Arg: %s\n", templ->args[i++]);
		}
		while (templ->redirect != NULL)
		{
			printf("\033[0;36m********* Redirection %d *********\033[0;0m\n", k++);
			printf("\033[0;37mType:\033[0;0m %c\n", templ->redirect->type);
			printf("\033[0;38mFile:\033[0;0m %s\n", templ->redirect->file);
			templ->redirect = templ->redirect->next;
		}
		templ = templ->next;
	}
	
}