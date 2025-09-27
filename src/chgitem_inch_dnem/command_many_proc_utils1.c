/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_many_proc_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:47:00 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/27 11:50:07 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	check_builtin_body(t_shell *shell, t_command *cmd)
{
	builtin_with_forks(shell, cmd);
	builtin_without_forks(shell, cmd);
	exit(g_exit_status);
}
