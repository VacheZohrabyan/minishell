/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_many_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:04:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/25 14:16:19 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	close_all_pipes(t_shell *shell)
{
	int	j;

	if (!shell->pipe_fd)
		return ;
	j = 0;
	while (j < shell->cmd_count - 1)
	{
		close(shell->pipe_fd[j][0]);
		close(shell->pipe_fd[j][1]);
		j++;
	}
}

void	execute_child(t_shell *shell, t_command *cmd, int i)
{
	t_redirect	*red;
	char		*str;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(shell, i);
	close_all_pipes(shell);
	red = cmd->redirect;
	if (red)
	{
		if (any(red) == -1)
			exit(1);
		check_redirect(cmd);
	}
	str = "";
	if (cmd->argv && cmd->argv[0])
		str = find_command_path(shell->env_list, cmd->argv[0]);
	if (check_builtin(shell, cmd))
	{
		builtin_with_forks(shell, cmd);
		builtin_without_forks(shell, cmd);
		exit(g_exit_status);
	}
	if (str)
		execv_function(shell, str, cmd, 0);
}

void	cleanup_and_wait(t_shell *shell)
{
	int	j;

	close_all_pipes(shell);
	j = 0;
	while (j < shell->cmd_count - 1)
	{
		free(shell->pipe_fd[j]);
		j++;
	}
	free(shell->pipe_fd);
	destroy_many_waitpid(shell);
	free(shell->pids);
}

void	command_many_proc(t_shell *shell)
{
	t_command	*tmp;
	int			i;
	pid_t		pid;

	i = -1;
	if (allocate_pipes(shell) || !shell->pipe_fd || create_pipes(shell) == -1)
		return ;
	if (allocate_pids(shell) || !shell->pids)
		return ;
	tmp = shell->command;
	while (tmp && i++ < shell->cmd_count)
	{
		if (shell->cmd_count == 1 && check_builtin(shell, tmp))
			check_redirect(tmp);
		else
		{
			pid = fork();
			if (pid == 0)
				execute_child(shell, tmp, i);
			else if (pid > 0)
				shell->pids[i] = pid;
		}
		tmp = tmp->next;
	}
	cleanup_and_wait(shell);
}
