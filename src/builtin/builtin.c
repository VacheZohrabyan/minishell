/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/30 19:36:16 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!shell->command->argv)
		return (0);
	else if (!ft_strcmp("pwd", shell->command->argv[0]))
		return (cmd_pwd());
	else if (!ft_strcmp("exit", shell->command->argv[0]))
		return (cmd_exit(shell));
	else if (!ft_strcmp("env", shell->command->argv[0]))
		return (cmd_env(shell->env_list));
	else if (!ft_strcmp("history", shell->command->argv[0]))
		return (cmd_history(shell));
	else if (!ft_strcmp("cd", shell->command->argv[0]))
		return (cmd_cd(shell));
	return (0);
}
