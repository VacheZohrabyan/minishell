/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:57:58 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 11:58:19 by vzohraby         ###   ########.fr       */
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

void	sig(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	destroy_one_waitpid(pid_t pid, t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_sig_quit);
	waitpid(pid, &shell->status, 0);
	sig();
	g_exit_status = shell->status % 256;
	if (WIFEXITED(shell->status) && WEXITSTATUS(shell->status) != 0)
	{
		g_exit_status = WEXITSTATUS(shell->status);
		return ;
	}
}

int	destroy_heredoc(pid_t pid, int status, int *pipefd, t_redirect *redirect)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	g_exit_status = status % 256;
	signal(SIGINT, handle_sigher);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_exit_status = WEXITSTATUS(status);
		close(pipefd[0]);
		return (-1);
	}
	redirect->fd = pipefd[0];
	return (0);
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
