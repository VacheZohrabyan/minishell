/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:30 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/20 16:17:57 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	handle_sigher(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	handle_sigcat(int sig)
{
	(void)sig;
	g_exit_status = 130;
}

void	ctrlc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
