/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:23 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 19:04:31 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H

# include "include.h"

void	sig(void);
void	handle_sigcat(int sig);
void	destroy_many_waitpid(t_shell *shell);
void	destroy_one_waitpid(pid_t pid, t_shell *shell);
void	handle_sig_quit(int sig);

#endif