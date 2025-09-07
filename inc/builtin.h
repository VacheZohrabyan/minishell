/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/04 19:18:05 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"

# define PATH_MAX 4096

int		cmd_pwd(void);
int		cmd_exit(t_shell *shell, t_command *command);
int		check_argument(t_command *command, char *err_msg);
int		cmd_env(t_env *env);
int		cmd_cd(t_shell *shell, t_command *command);
int		cmd_echo(t_command *command);
int		cmd_export(t_shell *shell, t_command *command);

// cmd_history.c
int		record_history(t_shell *shell, const char *line);
int		init_shell_history(t_shell *shell);
void	close_shell_history(t_shell *shell);
int		print_history(t_shell *shell);
int		history_c(t_shell *shell);
int		load_history(t_shell *shell);
int		cmd_history(t_shell *shell, t_command *command);

int		check_builtin(t_shell *shell, t_command *command);
#endif