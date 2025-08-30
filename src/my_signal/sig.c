/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:57:58 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/30 18:11:07 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	ctrlc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// rl_redisplay();
}

// void	sig(void)
// {
// 	struct sigaction sa_int;
// 	struct sigaction sa_quit;

// 	sa_int.sa_handler = ctrlc;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa_int, NULL);
// 	sa_quit.sa_handler = SIG_IGN;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

void	setup_shell_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = ctrlc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
