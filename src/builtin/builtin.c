/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/11 20:51:29 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell, t_command *command)
{
	if (!command->argv)
		return (0);
	else if (!ft_strcmp("pwd", command->argv[0]))
		return (cmd_pwd(), 0);
	else if (!ft_strcmp("exit", command->argv[0]))
		return (cmd_exit(shell, command), 0);
	else if (!ft_strcmp("env", command->argv[0]))
		return (cmd_env(shell->env_list), 0);
	else if (!ft_strcmp("history", command->argv[0]))
		return (cmd_history(shell, command), 0);
	else if (!ft_strcmp("cd", command->argv[0]))
		return (cmd_cd(shell, command), 0);
	else if (!ft_strcmp("echo", command->argv[0]))
		return (cmd_echo(command), 0);
	else if (!ft_strcmp("export", command->argv[0]))
		return (cmd_export(shell, command), 0);
	return (1);
}
