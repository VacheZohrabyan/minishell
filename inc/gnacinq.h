/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:20:29 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/20 19:00:17 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNACINQ_H
#define GNACINQ_H

#include "include.h"

int gnacinq(t_shell* command);
int	any(t_redirect *redirect);
int	heredoc_file_open_wr(t_redirect *redirect);
char	*find_command_path(t_env *env, char *cmd);

#endif