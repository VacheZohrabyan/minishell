/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:36:01 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/28 11:01:39 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	message_no_such_file(t_command *com, char **env_array)
{
	g_exit_status = 127;
	free_split(env_array);
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, com->argv[0], ft_strlen(com->argv[0]));
	write(STDERR_FILENO, ":  No such file or directory\n",
		ft_strlen(":  No such file or directory\n"));
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	exit(g_exit_status);
}

void	message_permission_denied(t_command *com, char **env_array)
{
	g_exit_status = 126;
	free_split(env_array);
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, com->argv[0], ft_strlen(com->argv[0]));
	write(STDERR_FILENO, ":  Permission denied\n",
		ft_strlen(":  Permission denied\n"));
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	exit(g_exit_status);
}

void	message_command_not_fount(t_command *com, char **env_array)
{
	g_exit_status = 127;
	free_split(env_array);
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, com->argv[0], ft_strlen(com->argv[0]));
	write(STDERR_FILENO, ": command not found\n",
		ft_strlen(": command not found\n"));
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	exit(g_exit_status);
}
