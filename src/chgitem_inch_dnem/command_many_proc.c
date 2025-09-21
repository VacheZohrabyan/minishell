/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_many_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:04:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/21 16:06:28 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void esel_chgitem(t_shell* shell, t_command* com)
{
	int saved_stdout = dup(STDOUT_FILENO);
	if (com->redirect && any(com->redirect) != -1)
		check_redirect(com);
	builtin_with_forks(shell, com);
	builtin_without_forks(shell, com);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return ;
}

int **allocate_pipes(int count)
{
	int **pipe_fd;
	int i;

	if (count <= 1)
		return (NULL);
	pipe_fd = (int **)malloc(sizeof(int *) * (count - 1));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (NULL);
		i++;
	}
	return (pipe_fd);
}

int create_pipes(int **pipe_fd, int count)
{
	int i;

	if (count <= 1 || !pipe_fd)
		return (0);
	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

pid_t *allocate_pids(int count)
{
	pid_t *pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!pids)
		return (NULL);
	return (pids);
}

void setup_child_pipes(int **pipe_fd, int i, int count)
{
	if (i > 0)
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
	if (i < count - 1)
		dup2(pipe_fd[i][1], STDOUT_FILENO);
}

void close_all_pipes(int **pipe_fd, int count)
{
	int j;

	if (!pipe_fd)
		return ;
	j = 0;
	while (j < count - 1)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		j++;
	}
}

void execute_child(t_shell *shell, t_command *cmd, int **pipe_fd, int i)
{
	t_redirect *red;
	char       *str;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	setup_child_pipes(pipe_fd, i, shell->cmd_count);
	close_all_pipes(pipe_fd, shell->cmd_count);

	red = cmd->redirect;
	if (red)
	{
		if (any(red) == -1)
			exit(1);
		check_redirect(cmd);
	}

	str = find_command_path(shell->env_list, cmd->argv[0]);
	if (check_builtin(shell, cmd))
	{
		builtin_with_forks(shell, cmd);
		builtin_without_forks(shell, cmd);
		exit(g_exit_status);
	}
	execv_function(str, cmd, 0);
}


void cleanup_and_wait(int **pipe_fd, pid_t *pids, int count, int status)
{
	int j;

	close_all_pipes(pipe_fd, count);
	j = 0;
	while (j < count - 1)
	{
		free(pipe_fd[j]);
		j++;
	}
	free(pipe_fd);
	destroy_many_waitpid(pids, status, count);
	free(pids);
}

void command_many_proc(t_shell *shell)
{
	int			**pipe_fd;
	pid_t		*pids;
	t_command	*tmp;
	int			i;
	int			status = 0;
	pid_t		pid;

	i = 0;
	pipe_fd = allocate_pipes(shell->cmd_count);
	if (!pipe_fd || create_pipes(pipe_fd, shell->cmd_count) == -1)
		return ;
	pids = allocate_pids(shell->cmd_count);
	if (!pids)
		return ;
	tmp = shell->command;
	while (tmp && i < shell->cmd_count)
	{
		if (shell->cmd_count == 1 && check_builtin(shell, tmp))
			check_redirect(tmp);
		else
		{
			pid = fork();
			if (pid == 0)
				execute_child(shell, tmp, pipe_fd, i);
			else if (pid > 0)
				pids[i] = pid;
		}
		tmp = tmp->next;
		i++;
	}
	cleanup_and_wait(pipe_fd, pids, shell->cmd_count, status);
}
