/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:20:29 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/21 15:30:50 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNACINQ_H
#define GNACINQ_H

#include "include.h"

int gnacinq(t_shell* command);
int	any(t_redirect *redirect);
int	heredoc_file_open_wr(t_redirect *redirect);
char	*find_command_path(t_env *env, char *cmd);
void execv_function(char* str, t_command* com, int flag);
void check_redirect(t_command* com);
void command_many_proc(t_shell *shell);
void	command_proc(t_shell *shell, t_command *com);

#endif