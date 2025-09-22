/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/22 12:07:24 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"

# define PATH_MAX 4096

int		cmd_pwd(void);
int		cmd_exit(t_shell *shell, t_command *command);
int		check_argument(t_command *command);
long	ft_atol(const char *str);
int		is_non_numeric(char *status);
int		cmd_env(t_env *env);
int		cmd_cd(t_shell *shell, t_command *command);
int		cmd_echo(t_command *command);
int		cmd_export(t_shell *shell, t_command *command);
int		cmd_unset(t_shell *shell, t_command *command);
// cmd_history.c
int		record_history(t_shell *shell, const char *line);
int		init_shell_history(t_shell *shell);
void	close_shell_history(t_shell *shell);
int		print_history(t_shell *shell);
int		history_c(t_shell *shell);
int		load_history(t_shell *shell);
int		cmd_history(t_shell *shell, t_command *command);
// export
int		is_valid_identifier(const char *str);
char	*get_key(char *arg);
void	print_export(t_env_node *head);
void	sort_export(t_env_node *head);
void	swap_env_nodes(t_env_node *a, t_env_node *b);

int		builtin_with_forks(t_shell *shell, t_command *command);
int		builtin_without_forks(t_shell *shell, t_command *command);
int		check_builtin(t_shell *shell, t_command *command);
void	free_shell(t_shell *shell);
#endif