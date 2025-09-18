/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:23 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/18 10:08:17 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H

# include "include.h"

void	ctrlc(int sig);
void  sig();
void	sig_handler_prompt(int sig);
void handle_sigher(int sig);
void handle_sigint(int sig);
void handle_sigcat(int sig);
void destroy_many_waitpid(pid_t* pids, int status, int count);
void destroy_one_waitpid(pid_t pid, int status);

#endif