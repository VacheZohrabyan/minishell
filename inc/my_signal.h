/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:23 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 12:08:28 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H

# include "include.h"

void	ctrlc(int sig);
void	sig(void);
void	sig_handler_prompt(int sig);
void	handle_sigher(int sig);
void	handle_sigint(int sig);
void	handle_sigcat(int sig);
void	destroy_many_waitpid(t_shell *shell);
void	destroy_one_waitpid(pid_t pid, t_shell *shell);
int		destroy_heredoc(pid_t pid, int status, int *pipefd,
			t_redirect *redirect);
void	handle_sig_quit(int sig);

#endif