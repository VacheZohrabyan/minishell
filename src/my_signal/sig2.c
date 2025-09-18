/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:30 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/18 11:36:35 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	handle_sigher(int sig)
{
	(void)sig;
	// write(1, "\n", 1);
	rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	handle_sigint(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
	// exit(130);
}

void	handle_sigcat(int sig)
{
	(void)sig;
	g_exit_status = 130;
	// write(STDOUT_FILENO, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	//rl_redisplay();
}

void	ctrlc(int sig)
{
	(void)sig;
	//
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
