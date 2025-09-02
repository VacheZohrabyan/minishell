/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/02 12:59:33 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"


int heredoc_file_open_wr(t_shell* shell, t_redirect *redirect)
{
	char* buffer;
	int pipefd[2];
	char* str;
	str = NULL;
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			printf("minishell: warning: here-document at line 75 delimited by end-of-file (wanted `ld')\n");
			return (-1);
			close(pipefd[1]);
		}
		write(pipefd[1], buffer, ft_strlen(buffer));
		write(pipefd[1], "\n", 1);
		str = ft_strjoin(str, buffer);
		str = ft_strjoin(str, "\n");
		if (!ft_strncmp(redirect->file_name, buffer, ft_strlen(buffer)))
			break;
		free(buffer);
		buffer = NULL;
	}
	record_history(shell, str);
	close(pipefd[0]);
	redirect->fd = pipefd[0];
	return (0);
}

int any_other(t_shell *shell)
{
	t_command* command = shell->command;
	int flag = 0;
	// if (!redirect)
	// 	return -1;
	while (command)
	{
		while (command->redirect)
		{
			if (command->redirect->token_type == TOKEN_REDIRECT_IN)// <
			{
				if ((command->redirect->fd = access(command->redirect->file_name, F_OK)) == -1)
				{
					printf("minishell: %s: No such file or directory\n", command->redirect->file_name);
					flag = -1;
				}
			}
			else if (command->redirect->token_type == TOKEN_HEREDOC) // <<
			{
				if (heredoc_file_open_wr(shell, command->redirect) == -1)
					flag = -1;
			}
			else if (command->redirect->token_type == TOKEN_REDIRECT_OUT)// >
			{
				if ((command->redirect->fd = open(command->redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
					flag = -1;
			}
			else // >>
			{
				if ((command->redirect->fd = open(command->redirect->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
					flag = -1;
			}
			command->redirect = command->redirect->next;
		}
		command = command->next;
	}
	return flag;
}

int any(t_shell *shell, t_redirect* redirect)
{
	t_redirect* tmp = redirect;
	// if (!redirect)
	// 	return -1;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)// <
		{
			check_builtin(shell);
			if ((tmp->fd = access(tmp->file_name, F_OK)) == -1)
			{
				printf("minishell: %s: No such file or directory\n", tmp->file_name);
				return -1;
			}
			dup2(tmp->fd, STDIN_FILENO);
			close(tmp->fd);
		}
		else if (tmp->token_type == TOKEN_HEREDOC) // <<
		{
			check_builtin(shell);
			if (heredoc_file_open_wr(shell, tmp) == -1)
				return (-1);
			dup2(tmp->fd, STDIN_FILENO);
            close(tmp->fd);
		}
		else if (tmp->token_type == TOKEN_REDIRECT_OUT)// >
		{			
			check_builtin(shell);
			if ((tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
				return -1;
			dup2(tmp->fd, STDOUT_FILENO);
            close(tmp->fd);
		}
		else // >>
		{
			check_builtin(shell);
			if ((tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
				return -1;
			dup2(tmp->fd, STDOUT_FILENO);
            close(tmp->fd);
		}
		tmp = tmp->next;
	}
	return 0;
}

void command_proc(t_command* com)
{
	pid_t pid = fork();
	int status;
	if (pid < 0)
	{
		printf("error fork()\n");
		return;
	}
	else if (pid == 0)
	{
		// dup2(com->redirect->fd, STDOUT_FILENO);
		// if ((any(shell, com->redirect) != -1))
		// {
		// 	dup2(com->redirect->fd, STDOUT_FILENO);
		// 	close(com->redirect->fd);
		// }
		char* str = ft_strjoin("/bin/", com->argv[0]);
		setup_child_signals();
		if (execv(str, com->argv) == -1)
		{
			perror("Execv faild");
			exit(0);
		}
		free(str);
		// close(com->redirect->fd);
	}
	waitpid(pid, &status, 0);
}

void command_many_proc(t_shell* shell, int count)
{
	int** pipe_fd;
	t_command* tmp = shell->command;
	pid_t* pids;
	pipe_fd = (int**)malloc(sizeof(int*) * (count - 1));
	if (!pipe_fd)
		return;
	pids = (pid_t*)malloc(sizeof(pid_t) * count);
	int i = 0;
	if (count > 1)
	{
		while (i < count - 1)
		{
			pipe_fd[i] = (int*)malloc(sizeof(int) * 2);
			if (!pipe_fd[i] || (pipe(pipe_fd[i]) == -1))
			{
				while (i)
				{
					--i;
					free(pipe_fd[i]);
					pipe_fd[i] = NULL;
				}
				free(pipe_fd);
				pipe_fd = NULL;
				return;
			}		
			++i;
		}
	}
	i = 0;
	while (tmp && i < count)
	{
		pid_t pid = fork();
		if (pid < 0)
			return;
		else if (pid == 0)
		{
			if (i > 0)
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			if (i < count - 1)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			int j = 0;
			while (j < count - 1 && count > 1)
			{
				close(pipe_fd[j][0]);
				close(pipe_fd[j][1]);
				++j;
			}
			printf("stex\n");
			// if ((any(shell, tmp->redirect) != -1))
			// {
			// 	printf("mtav\n");
			// 	dup2(tmp->redirect->fd, STDOUT_FILENO);
			// 	close(tmp->redirect->fd);
			// }
			setup_child_signals();
			char* str = ft_strjoin("/bin/", tmp->argv[0]);
			if (execv(str, tmp->argv) == -1)
			{
				printf("command_many_proc execv faild\n");
				return ;
			}
			free(str);
		}
		else 
			pids[i] = pid;
		tmp = tmp->next;
		++i;
	}
	int j = 0;
	while (j < count - 1)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		free(pipe_fd[j]);
		++j;
	}
	free(pipe_fd);
	i = 0;
	int status = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		++i;
	}
	free(pids);
}

int gnacinq(t_shell* shell)
{
	t_command *tmp = shell->command;
	if (!tmp->argv)
	{
		while (tmp->redirect)
		{
			if (any(shell, tmp->redirect) == -1)
				return -1;
			tmp->redirect = tmp->redirect->next;
		}
	}
	else if (!(tmp->next) && tmp->argv)
	{
		if (tmp->redirect)
		{
			if (any(shell, tmp->redirect) == -1)
				return -1;
		}
		command_proc(tmp);
	}
	else
	{
		int count = 0;
		while (tmp)
		{
			++count;
			tmp = tmp->next;
		}
		if (any_other(shell) == -1)
			return -1;
		command_many_proc(shell, count);
	}
	return 0;
}