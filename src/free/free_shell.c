/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:37:11 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/26 12:24:55 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	free_shell(t_shell *shell)
{
	int	j;

	free_command(&(shell->command));
	token_node_free(&shell->token);
	free_env(&(shell->env_list));
	free_env(&(shell->export_list));
	free(shell->history);
	if (shell->pids)
		free(shell->pids);
	if (shell->buffer)
		free(shell->buffer);
	if (shell->pipe_fd)
	{
		j = 0;
		while (j < shell->cmd_count - 1)
		{
			free(shell->pipe_fd[j]);
			shell->pipe_fd[j] = NULL;
			j++;
		}
		free(shell->pipe_fd);
		shell->pipe_fd = NULL;
	}
	free(shell);
}
