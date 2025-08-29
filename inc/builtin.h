/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/29 13:08:12 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"

#define PATH_MAX        4096

int	cmd_pwd(void);
int	cmd_exit(t_shell *shell);
int	cmd_env(t_env *env);
int	check_builtin(t_shell *shell);

#endif