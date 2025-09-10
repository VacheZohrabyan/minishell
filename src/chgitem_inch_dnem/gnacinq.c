/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/10 20:08:18 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"


int heredoc_file_open_wr(t_shell* shell, t_redirect *redirect)
{
	char* buffer;
	int pipefd[2];
	char* str;
	str = NULL;
	buffer = NULL;
	
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			printf("minishell: warning: here-document at line 75 delimited by end-of-file (wanted `ld')\n");
			close(pipefd[1]);
			return (-1);
		}
		write(pipefd[1], buffer, ft_strlen(buffer));
		write(pipefd[1], "\n", 1);
		if (!ft_strcmp(redirect->file_name, buffer))
			break;
		free(buffer);
		close(pipefd[1]);
	}
	record_history(shell, str);
	redirect->fd = pipefd[0];
	return (0);
}

int any_other(t_shell *shell, t_redirect* redirect)
{
	t_redirect* red = redirect;
	int flag = 0;
	while (red)
	{
		if (red->token_type == TOKEN_REDIRECT_IN)// <
		{
			if ((red->fd = open(red->file_name, O_RDONLY)) == -1)
			{
				printf("minishell: %s: No such file or directory\n", red->file_name);
				return (-1);
			}
		}
		else if (red->token_type == TOKEN_HEREDOC) // <<
		{
			if (heredoc_file_open_wr(shell, red) == -1)
				flag = -1;
		}
		else if (red->token_type == TOKEN_REDIRECT_OUT)// >
		{
			if ((red->fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
			{
				printf("chexav\n");
				flag = -1;
			}
		}
		else if (red->token_type == TOKEN_REDIRECT_APPEND) 
		{
			if ((red->fd = open(red->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
				flag = -1;
		}
		red = red->next;
	}
	return flag;
}

int any(t_shell *shell, t_redirect* redirect)
{
	t_redirect* tmp = redirect;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)// <
		{
			if ((tmp->fd = open(tmp->file_name, O_RDONLY)) == -1)
			{
				perror(tmp->file_name);
				return -1;
			}
			tmp->to = STDIN_FILENO;
		}
		else if (tmp->token_type == TOKEN_HEREDOC) // <<
		{
			if (heredoc_file_open_wr(shell, tmp) == -1)
				return (-1);
			tmp->to = STDOUT_FILENO;
		}
		else if (tmp->token_type == TOKEN_REDIRECT_OUT)// >
		{			
			if ((tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
				return -1;
			tmp->to = STDOUT_FILENO;
		}
		else if (tmp->token_type == TOKEN_REDIRECT_APPEND) // >>
		{
			if ((tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
				return -1;
			tmp->to = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
	return 0;
}

char *find_command_path(char *cmd)
{
    char *path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    char **paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;

    char *full_path = NULL;
    int i = 0;

    while (paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (access(full_path, X_OK) == 0)
        {
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return full_path;
        }

        free(full_path);
        full_path = NULL;
        i++;
    }
    int j = 0;
    while (paths[j])
        free(paths[j++]);
    free(paths);

    return NULL;
}

void handle_sigcat(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void command_proc(t_shell *shell, t_command* com)
{
	pid_t pid = fork();
	int status;
	signal(SIGINT, handle_sigcat);
	
	if (pid < 0)
	{
		printf("error fork()\n");
		return;
	}
	else if (pid == 0)
	{
    	signal(SIGQUIT, SIG_DFL);
		char* str = find_command_path(com->argv[0]);
		if (com->redirect)
		{
			if (any(shell, com->redirect) == -1)
				return ;
		}
		if (check_builtin(shell, com))
		{
			dup2(com->redirect->fd, STDOUT_FILENO);
			close(com->redirect->fd);
			waitpid(pid, &status, 0);
			return;
		}		
		if (execv(str, com->argv) == -1)
		{
			free(str);
			perror("Ex ecv faild");
			return;
		}
		close(com->redirect->fd);
		free(str);
	}
	else
	{
		// signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		waitpid(pid, &status, 0);
		
		signal(SIGINT, SIG_DFL);
		sig();
		// signal(SIGQUIT, SIG_IGN);
		// restore prompt handler after child exits
			
	}
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
			while (j < count - 1)
			{
				close(pipe_fd[j][0]);
				close(pipe_fd[j][1]);
				++j;
			}
			t_redirect *red = tmp->redirect;
			while (red) 
			{
                if (any(shell, red) == -1)
                    exit(EXIT_FAILURE);
                if (dup2(red->fd, red->to) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(red->fd);
                red = red->next;
            }
			char* str = find_command_path(tmp->argv[0]);
			if (check_builtin(shell, tmp)) {
				exit(EXIT_SUCCESS);  // run builtin, then exit
			}
			else if (execv(str, tmp->argv) == -1)
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
	// if (!tmp->argv)
	// {
	// 	while (tmp->redirect)
	// 	{
	// 		printf("redirect = %s\n", tmp->redirect->file_name);
	// 		if (any(shell, tmp->redirect) == -1)
	// 			return -1;
	// 		tmp->redirect = tmp->redirect->next;
	// 	}
	// }
	if (!(tmp->next) && tmp->argv)
	{
		printf("argv = %s\n", tmp->argv[1]);
		command_proc(shell, shell->command);
	}
	else
	{
		int count = 0;
		while (tmp)
		{
			++count;
			tmp = tmp->next;
		}
		command_many_proc(shell, count);
	}
	return 0;
}