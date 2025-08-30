/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/30 14:35:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!shell->command->argv)
		return (0);
	else if (!ft_strncmp("pwd", shell->command->argv[0], ft_strlen(shell->command->argv[0])))
		return (cmd_pwd());
	else if (!ft_strncmp("exit", shell->command->argv[0], ft_strlen(shell->command->argv[0])))
		return (cmd_exit(shell));
	else if (!ft_strncmp("env", shell->command->argv[0], ft_strlen(shell->command->argv[0])))
		return (cmd_env(shell->env_list));
	else if (!ft_strncmp("history", shell->command->argv[0], ft_strlen(shell->command->argv[0])))
		return (cmd_history(shell));
	return (0);
}
