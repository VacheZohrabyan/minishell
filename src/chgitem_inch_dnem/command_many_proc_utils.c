/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_many_proc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:16:59 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 12:00:46 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	esel_chgitem(t_shell *shell, t_command *com)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (com->redirect && any(com->redirect) != -1)
		check_redirect(com);
	builtin_with_forks(shell, com);
	builtin_without_forks(shell, com);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return ;
}

int	allocate_pipes(t_shell *shell)
{
	int	i;

	if (shell->cmd_count <= 1)
		return (shell->pipe_fd = NULL, 1);
	shell->pipe_fd = (int **)malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipe_fd)
		return (shell->pipe_fd = NULL, 1);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipe_fd[i] = NULL;
		shell->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!shell->pipe_fd[i])
		{
			while (i != 0)
				free(shell->pipe_fd[i--]);
			free(shell->pipe_fd);
			return (shell->pipe_fd = NULL, 1);
		}
		i++;
	}
	return (0);
}

int	create_pipes(t_shell *shell)
{
	int	i;

	if (shell->cmd_count <= 1 || !shell->pipe_fd)
		return (0);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (pipe(shell->pipe_fd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	allocate_pids(t_shell *shell)
{
	if (shell->pids)
		free(shell->pids);
	shell->pids = (pid_t *)malloc(sizeof(pid_t) * (shell->cmd_count));
	if (!shell->pids)
		return (shell->pids = NULL, 1);
	return (0);
}

void	setup_child_pipes(t_shell *shell, int i)
{
	if (i > 0)
		dup2(shell->pipe_fd[i - 1][0], STDIN_FILENO);
	if (i < shell->cmd_count - 1)
		dup2(shell->pipe_fd[i][1], STDOUT_FILENO);
}
