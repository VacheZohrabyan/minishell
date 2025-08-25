/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/25 22:39:43 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> //Path_max -i hamar

int	cmd_pwd(void);
int	cmd_exit(t_shell *shell);
int	check_builtin(t_shell *shell);

#endif