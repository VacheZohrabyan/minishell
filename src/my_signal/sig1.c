/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:57:58 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 17:33:47 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	sig_handler_prompt(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 130;
}

static void	ctrlc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig(void)
{
	signal(SIGINT, ctrlc);
	g_exit_status = 130;
	signal(SIGQUIT, SIG_IGN);
}

// static void	set_signal(int sig, void (*handler)(int))
// {
// 	struct sigaction sa;

// 	sa.sa_handler = handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(sig, &sa, NULL);
// }

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_exit_status = 130;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);   // clear current input
// 	rl_redisplay();
// }

void	destroy_one_waitpid(pid_t pid, t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_sig_quit);
	waitpid(pid, &shell->status, 0);
	g_exit_status = 130;
	if (WIFEXITED(shell->status) && WEXITSTATUS(shell->status) != 0)
	{
		g_exit_status = WEXITSTATUS(shell->status);
		return ;
	}
	signal(SIGINT, handle_sigcat);
	signal(SIGQUIT, SIG_IGN);
}

void	destroy_many_waitpid(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->pids[i], &shell->status, 0);
		if (i == shell->cmd_count - 1)
		{
			if (WIFEXITED(shell->status))
				g_exit_status = WEXITSTATUS(shell->status);
			else if (WIFSIGNALED(shell->status))
				g_exit_status = 128 + WTERMSIG(shell->status);
		}
		i++;
	}
}
