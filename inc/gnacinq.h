/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:20:29 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/27 12:03:43 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNACINQ_H
# define GNACINQ_H

# include "include.h"

int		gnacinq(t_shell *command);
int		any(t_redirect *redirect);
int		heredoc_file_open_wr(t_redirect *redirect);
char	*find_command_path(t_env *env, char *cmd, int *status);
void	execv_function(t_shell *shell, char *str, t_command *com, int flag);
void	check_redirect(t_command *com);
void	command_many_proc(t_shell *shell);
void	command_proc(t_shell *shell, t_command *com);
void	check_builtin_body(t_shell *shell, t_command *cmd);
void	setup_child_pipes(t_shell *shell, int i);
void	esel_chgitem(t_shell *shell, t_command *com);
int		create_pipes(t_shell *shell);
int		allocate_pipes(t_shell *shell);
int		allocate_pids(t_shell *shell);
int		absolute_path(int *status, char *cmd);
void	message_no_such_file(t_command *com, char **env_array);
void	message_permission_denied(t_command *com, char **env_array);
void	message_command_not_fount(t_command *com, char **env_array);

#endif