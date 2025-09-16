/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:57:58 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 10:09:42 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void handle_sigher(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	
	exit(130);
}

void handle_sigcat(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
}

void	ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void sig()
{
	signal(SIGINT,ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void destroy_one_waitpid(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	waitpid(pid, &status, 0);
	g_exit_status = status % 255;
	signal(SIGINT, handle_sigher);
	signal(SIGQUIT, SIG_IGN);	sig();
}

void destroy_many_waitpid(pid_t* pids, int status, int count)
{
	int i = 0;
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
	g_exit_status = status % 255;
    signal(SIGINT, handle_sigher);
    signal(SIGQUIT, SIG_IGN);
	sig();
}
