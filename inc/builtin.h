/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/29 18:54:38 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"

# define PATH_MAX 4096
char	*get_env_param(t_env *env, char *key);
int		cmd_pwd(void);
int		cmd_exit(t_shell *shell);
int		cmd_env(t_env *env);
int		check_builtin(t_shell *shell);

int		record_history(t_shell *shell, const char *line);
int		init_shell_history(t_shell *shell);
void	close_shell_history(t_shell *shell);
int		cmd_history(t_shell *shell);

#endif