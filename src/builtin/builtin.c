/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/02 12:57:26 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell, t_command *command)
{
	if (!command->argv)
		return (0);
	else if (!ft_strcmp("pwd", command->argv[0]))
		return (cmd_pwd());
	else if (!ft_strcmp("exit", command->argv[0]))
		return (cmd_exit(shell, command));
	else if (!ft_strcmp("env", command->argv[0]))
		return (cmd_env(shell->env_list));
	else if (!ft_strcmp("history", command->argv[0]))
		return (cmd_history(shell, command));
	else if (!ft_strcmp("cd", command->argv[0]))
		return (cmd_cd(shell, command));
	return (0);
}
