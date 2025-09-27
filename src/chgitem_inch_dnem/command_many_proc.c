/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_many_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:04:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/27 11:48:47 by vzohraby         ###   ########.fr       */
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
		str = find_command_path(shell->env_list,
				cmd->argv[0], &(shell->status));
	if (check_builtin(shell, cmd))
		check_builtin_body(shell, cmd);
	else if (str)
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
		shell->pipe_fd[j] = NULL;
		j++;
	}
	free(shell->pipe_fd);
	shell->pipe_fd = NULL;
	destroy_many_waitpid(shell);
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
