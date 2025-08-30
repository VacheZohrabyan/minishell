/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/30 15:00:16 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"


int heredoc_file_open_wr(t_shell* shell, t_redirect *redirect)
{
	int fd = 0;
	char* buffer;
	fd = open(redirect->file_name, O_RDWR | O_CREAT, 0777);
	if (fd != -1)
	{
		while (1)
		{
			buffer = readline(">");
			if (!buffer)
			{
				printf("minishell: warning: here-document at line 75 delimited by end-of-file (wanted `ld')\n");
				return (-1);
			}
			else if (buffer[0] == '\n')
			write(fd, buffer, ft_strlen(buffer));
			write(fd, "\n", 1);
			if (!ft_strncmp(redirect->file_name, buffer, ft_strlen(buffer)))
				break;
		}
	}
	char* str = NULL;
	buffer = NULL;
	while ((buffer = get_next_line(fd)))
	{
		str = ft_strjoin_gnl(str, buffer);
		free(buffer);
		buffer = NULL;
	}
	record_history(shell, str);
	close(fd);
	return (0);
}

int any(t_shell *shell, t_redirect* redirect)
{
	t_redirect* tmp = redirect;
	// printf("any\n");
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)
		{
			// printf("any-redirection\n");
			if ((tmp->fd = access(tmp->file_name, F_OK)) == -1)
			{
				printf("minishell: %s: No such file or directory\n", tmp->file_name);
				return -1;
			}
			// printf("any-redirection-verch\n");
		}
		else if (tmp->token_type == TOKEN_HEREDOC)
		{
			// printf("any-herdoc\n");
			if (heredoc_file_open_wr(shell, tmp) == -1)
				return (-1);
			// printf("any-herdoc-verch\n");
		}
		else 
		{
			// printf("any-else\n");
			if ((tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT, 0664)) < 0)
				return -1;
			// printf("any-else-verch\n");
		}
		tmp = tmp->next;
	}
	// printf("any-verch\n");
	return 0;
}

void command_proc(t_command* com)
{
	pid_t pid = fork();
	int status;
	char* str = ft_strjoin("/bin/", com->argv[0]);
	if (pid < 0)
	{
		printf("error fork()\n");
		return;
	}
	else if (pid == 0)
	{
		// dup2(com->redirect->fd, STDOUT_FILENO);
		
		if (execv(str, com->argv) == -1)
		{
			perror("Execv faild");
			exit(0);
		}
		close(com->redirect->fd);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(str);
		str = NULL;
	}
}

void command_many_proc(t_command* com, int count)
{
	int** pipe_fd;
	t_command* tmp = com;
	pipe_fd = (int**)malloc(sizeof(int*) * count);
	if (!pipe_fd)
		return;
	int i = 0;
	while (i < count)
	{
		pipe_fd[i] = (int*)malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
		{
			while (i)
			{
				free(pipe_fd[i]);
				pipe_fd[i] = NULL;
				--i;
			}
			free(pipe_fd);
			pipe_fd = NULL;
			return;
		}		
		++i;
	}
	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
		{
			while (i)
			{
				free(pipe_fd[i]);
				pipe_fd[i] = NULL;
				--i;
			}
			free(pipe_fd);
			pipe_fd = NULL;
			return ;
		}
		++i;
	}
	i = 0;
	while (tmp && i < count)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			return;
		}
		else if (pid == 0)
		{
			if (i > 0)
				dup2(pipe_fd[i - 1][1], STDIN_FILENO);
			if (i < count - 1)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			
			int j = 0;
			while (j < count - 1)
			{
				close(pipe_fd[j][0]);
				close(pipe_fd[j][1]);
				++j;
			}
			char* str = ft_strjoin("/bin/", com->argv[0]);
			if (execv(str, tmp->argv) == -1)
			{
				printf("command_many_proc execv faild\n");
				return ;
			}
		}
		tmp = tmp->next;
		++i;
	}
	int j = 0;
	while (j < count - 1)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
		++j;
	}
	i = 0;
	while (i < count)
	{
		wait(NULL);
		++i;
	}
}

int gnacinq(t_shell* shell)
{
	t_command *tmp = shell->command;
	if (!tmp->argv)
	{
		// printf("gnacinq\n");
		while (tmp->redirect)
		{
			if (any(shell, tmp->redirect) == -1)
				return -1;
			tmp->redirect = tmp->redirect->next;
		}
		// printf("gnacinq-verch\n");
	}
	else if (!(tmp->next) && tmp->argv)
	{
		// printf("gnacinq else if\n");
		if (any(shell, tmp->redirect) == -1)
			return -1;
		command_proc(tmp);
		// printf("gnacinq else if\n");
	}
	else
	{
		int count = 0;
		while (tmp)
		{
			++count;
			if (any(shell, tmp->redirect) == -1)
				return -1;
			tmp = tmp->next;
		}
		tmp = shell->command;
		command_many_proc(tmp, count);
	}
	return 0;
}