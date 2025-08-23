/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/23 18:03:19 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	cmd_pwd(void);
int	cmd_exit(t_shell *shell);
int	check_builtin(t_shell *shell);

#endif