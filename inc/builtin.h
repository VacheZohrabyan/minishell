/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:19:05 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/17 16:31:16 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "include.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	cmd_pwd(void);
int	check_builtin(char *cmd);

#endif