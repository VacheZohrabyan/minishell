/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/20 19:29:27 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void execv_function(char* str, t_command* com, int flag)
{
	if (execv(str, com->argv) == -1)
	{
		free(str);
		write(STDOUT_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDOUT_FILENO, com->argv[0], ft_strlen(com->argv[0]));
		write(STDOUT_FILENO, ": command not found\n", ft_strlen(": command not found\n"));
		close(com->redirect->fd);
		g_exit_status = 127;
		if (flag)
			return;
		else
			exit(127);
	}
}

void check_redirect(t_command* com)
{
	t_redirect* r;

	r = com->redirect;
	while (r)
	{
		if (r->fd >= 0)
		{
			dup2(r->fd, r->to);
			close(r->fd);
		}
		r = r->next;
	}
}

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

void	command_proc(t_shell *shell, t_command *com)
{
	pid_t		pid;
	int			status;
	char		*str;
	t_redirect* r;
	if (check_builtin(shell, com))
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
	pid = fork();
	status = 0;
	if (pid < 0)
	{
		write (STDOUT_FILENO, "error fork()\n", ft_strlen("error fork()\n"));
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		str = find_command_path(shell->env_list, com->argv[0]);
		check_redirect(com);
		execv_function(str, com, 1);
		close(com->redirect->fd);
		free(str);
	}
	else
		destroy_one_waitpid(pid, status);
		
}

void command_many_proc(t_shell *shell, int count)
{
    int         **pipe_fd;
    t_command   *tmp;
    pid_t       *pids;
    int         i;
    pid_t       pid;
    t_redirect  *red;
    char        *str;
    int         j;
    t_redirect  *r;
	int status = 0;

    tmp = shell->command;
    pipe_fd = (int **)malloc(sizeof(int *) * (count - 1));
    if (!pipe_fd)
        return ;
    pids = (pid_t *)malloc(sizeof(pid_t) * count);
    if (!pids)
        return ;
    i = 0;
    if (count > 1)
    {
        while (i < count - 1)
        {
            pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
            if (!pipe_fd[i] || (pipe(pipe_fd[i]) == -1))
                return ;
            ++i;
        }
    }
    i = 0;
    while (tmp && i < count)
    {
        if (count == 1 && check_builtin(shell, tmp))
		{
			int saved_stdout = dup(STDOUT_FILENO);
			if (tmp->redirect && any(tmp->redirect) != -1)
				check_redirect(tmp);
			builtin_without_forks(shell, tmp);
			builtin_with_forks(shell, tmp);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			tmp = tmp->next;
			i++;
        }
		else
		{
			pid = fork();
			if (pid < 0)
				return ;
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (i > 0)
					dup2(pipe_fd[i - 1][0], STDIN_FILENO);
				if (i < count - 1)
					dup2(pipe_fd[i][1], STDOUT_FILENO);
				j = 0;
				while (j < count - 1)
				{
					close(pipe_fd[j][0]);
					close(pipe_fd[j][1]);
					++j;
				}
				red = tmp->redirect;
				if (red)
				{
					if (any(red) == -1)
						exit(1);
					check_redirect(tmp);
				}
				str = find_command_path(shell->env_list, tmp->argv[0]);
				if (check_builtin(shell, tmp))
				{
					builtin_with_forks(shell, tmp);
					builtin_without_forks(shell, tmp);
					exit(g_exit_status);
				}
				execv_function(str, tmp, 0);
			}
			else
				pids[i] = pid;
		}
		tmp = tmp->next;
		++i;
    }
    j = 0;
    while (j < count - 1)
    {
        close(pipe_fd[j][0]);
        close(pipe_fd[j][1]);
        free(pipe_fd[j]);
        ++j;
    }
    destroy_many_waitpid(pids, status, count);
    free(pipe_fd);
    free(pids);
}

int	gnacinq(t_shell *shell)
{
	t_command *tmp = shell->command;
	int count = 0;
	t_command *cmd = tmp;
	while (cmd)
	{
		t_redirect *red = cmd->redirect;
		while (red)
		{
			if (red->token_type == TOKEN_HEREDOC)
			{
				if (heredoc_file_open_wr(red) == -1)
					return (0);
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	cmd = tmp;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	if (count == 1)
		command_proc(shell, shell->command);
	else if (count > 1)
		command_many_proc(shell, count);
	return (0);
}