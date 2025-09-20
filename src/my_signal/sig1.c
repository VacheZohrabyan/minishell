/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:57:58 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/20 16:12:32 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	sig_handler_prompt(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "^C\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
	g_exit_status = 130;
}

void	sig(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void	destroy_one_waitpid(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, handle_sig_quit);
    waitpid(pid, &status, 0);
    sig();
    g_exit_status = status % 256;
    write (1, "\n", 1);
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    {
        g_exit_status = WEXITSTATUS(status);
        // close(pipefd[0]);
        return ;
    }
    // redirect->fd = pipefd[0];
}

void destroy_many_waitpid(pid_t *pids, int status, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        if (i == count - 1)
        {
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_exit_status = 128 + WTERMSIG(status);
        }
        i++;
    }
}
