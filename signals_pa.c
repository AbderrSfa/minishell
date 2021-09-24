/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_pa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 10:28:45 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/24 10:44:58 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* void	sig_quit(int signal)
{
	if (signal == SIGQUIT && sig.quit_flag == 0)
		sig.quit_flag = 1;
	else if (signal == SIGQUIT && sig.quit_flag == 1)
		ft_putstr("\b\b  \b\b");
	//return ;
} */

void	sig_int(int signal)
{
	// if (signal == SIGINT && sig.interrupt_flag == 0)
	// {
	// 	sig.interrupt_flag = 1;
	// 	ft_putstr("\nminishell-1.0$ ");
	// }
	// else if (signal == SIGINT && sig.interrupt_flag == 1)
	// 	ft_putstr("\b\b  \b\b\nminishell-1.0$ ");
	//ft_putstr_fd("\b\b", 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig.ret = 1;
}
