/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:30 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 17:39:14 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	handle_sig_quit(int sig)
{
	(void)sig;
	write (STDERR_FILENO, "Quit (core dumped)\n",
		ft_strlen("Quit (core dumped)\n"));
	g_exit_status = 131;
}

void	handle_sigcat(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write (2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
