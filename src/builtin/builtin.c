/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 18:27:42 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

static int	chlp(t_shell *shell, t_command *command)
{
	char	*tmp;

	if (ft_strcmp(command->argv[0], "$?") == 0 && !(shell->status))
	{
		tmp = ft_itoa(g_exit_status);
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = NULL;
		write(STDERR_FILENO, ": command not found\n",
			ft_strlen(": command not found\n"));
		g_exit_status = 127;
		return (1);
	}
	return (0);
}

int	check_builtin(t_shell *shell, t_command *command)
{
	(void)shell;
	if (!command->argv)
		return (0);
	else if (chlp(shell, command))
		return (1);
	else if (!ft_strcmp("pwd", command->argv[0]))
		return (1);
	else if (!ft_strcmp("exit", command->argv[0]))
		return (1);
	else if (!ft_strcmp("env", command->argv[0]))
		return (1);
	else if (!ft_strcmp("history", command->argv[0]))
		return (1);
	else if (!ft_strcmp("cd", command->argv[0]))
		return (1);
	else if (!ft_strcmp("echo", command->argv[0]))
		return (1);
	else if (!ft_strcmp("export", command->argv[0]))
		return (1);
	else if (!ft_strcmp("unset", command->argv[0]))
		return (1);
	return (0);
}

int	builtin_with_forks(t_shell *shell, t_command *command)
{
	if (!ft_strcmp("pwd", command->argv[0]))
		return (cmd_pwd(), 1);
	else if (!ft_strcmp("exit", command->argv[0]))
		return (cmd_exit(shell, command), 1);
	else if (!ft_strcmp("env", command->argv[0]))
		return (cmd_env(shell->env_list), 1);
	else if (!ft_strcmp("history", command->argv[0]))
		return (cmd_history(shell, command), 1);
	return (0);
}

int	builtin_without_forks(t_shell *shell, t_command *command)
{
	if (!ft_strcmp("cd", command->argv[0]))
		return (cmd_cd(shell, command), 1);
	else if (!ft_strcmp("echo", command->argv[0]))
		return (cmd_echo(command, &(shell->status)), 1);
	else if (!ft_strcmp("export", command->argv[0]))
		return (cmd_export(shell, command), 1);
	else if (!ft_strcmp("unset", command->argv[0]))
		return (cmd_unset(shell, command), 1);
	return (0);
}
