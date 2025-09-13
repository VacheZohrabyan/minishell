/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/13 12:57:27 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"
int heredoc_file_open_wr(t_redirect *redirect)
{
    char *buffer;
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return -1;

    pid = fork();
    if (pid < 0)
        return -1;

    if (pid == 0) // child
    {
        close(pipefd[0]);
        signal(SIGINT, handle_sigint); // custom
        while (1)
        {
            buffer = readline(">");
            if (!buffer) // EOF (Ctrl+D)
            {
                fprintf(stderr, "minishell: warning: here-document delimited by EOF (wanted `%s`)\n",
                        redirect->file_name);
                close(pipefd[1]);
                exit(0);
            }
            if (ft_strcmp(redirect->file_name, buffer) == 0) // delimiter match
            {
                free(buffer);
                close(pipefd[1]);
                exit(0);
            }
            write(pipefd[1], buffer, ft_strlen(buffer));
            write(pipefd[1], "\n", 1);
            free(buffer);
        }
    }
    else // parent
    {
        int status;
        close(pipefd[1]);
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        signal(SIGINT, handle_sigher);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            close(pipefd[0]);
            return -1;
        }
        redirect->fd = pipefd[0];
    }
    return 0;
}

int any(t_redirect* redirect)
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

int absolute_path(char* cmd)
{
	if (cmd[0] == '/')
		return 1;
	else if (cmd[0] == '.' && cmd[1] == '/')
		return 1;
	return 0;
}

char *find_command_path(char *cmd)
{
	if (absolute_path(cmd))
		return ft_strdup(cmd);
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

void shlvl_increment(t_shell* shell, char *str)
{
	printf("ha\n");
	size_t i = 0;
	if (str[0] == '.' && str[1] == '/')
	{
		while (shell->env_list->buffer_env[i])
			++i;
		t_env_node* env = shell->env_list->buffer_env[i - 1];
		while (env)
		{
			if (ft_strcmp(env->key, "SHLVL") == 0)
			{
				int value = ft_atoi(env->value);
				++value;
				free(env->value);
				printf("value = %d\n", value);
				env->value = ft_strdup(ft_itoa(value));
				break;
			}
			env = env->next;
		}
	}
}

void command_proc(t_shell *shell, t_command* com)
{
	pid_t pid = fork();
	int status = 0;
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
			if (any(com->redirect) == -1)
			{
				destroy_one_waitpid(pid, status);
				return ;
			}
		}
		if (str[0] == '.' && str[1] == '/')
		{
			size_t i = 0;
			while (shell->env_list->buffer_env[i])
				++i;
			t_env_node* env = shell->env_list->buffer_env[i];
			while (env)
			{
				if (ft_strcmp(env->key, "SHLVL"))
				{
					int str = ft_atoi(env->value);
					set_env_param(env, "SHLVL", ft_itoa(++str));
					break;
				}
				env = env->next;
			}
		}
		if (!check_builtin(shell, com))
		{
			dup2(com->redirect->fd, STDOUT_FILENO);
			close(com->redirect->fd);
			destroy_one_waitpid(pid, status);
			return;
		}
		else if (execv(str, com->argv) == -1)
		{
			free(str);
			write(2, "minishell: ", ft_strlen("minishell: "));
			write(2, com->argv[0], ft_strlen(com->argv[0]));
			write(2, ": command not found\n", ft_strlen(": command not found\n"));
			// destroy_one_waitpid(pid, status);
			return;
		}
		close(com->redirect->fd);
		free(str);
	}
	else
	{
		destroy_one_waitpid(pid, status);		
	}
}

void command_many_proc(t_shell* shell, int count)
{
	int** pipe_fd;
	t_command* tmp = shell->command;
	pid_t* pids;
	int status = 0;
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
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
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
				if (red->token_type != TOKEN_HEREDOC && any(red) == -1)
				{
					destroy_many_waitpid(pids, status, count);
					exit(0);
				}
				dup2(red->fd, red->to);
				close(red->fd);
                red = red->next;
            }
			char* str = find_command_path(tmp->argv[0]);
			if (!check_builtin(shell, tmp)) {
				exit(EXIT_SUCCESS);
			}
			else if (execv(str, tmp->argv) == -1)
			{
				write(2, "minishell: ", ft_strlen("minishell: "));
				write(2, tmp->argv[0], ft_strlen(tmp->argv[0]));
				write(2, ": command not found\n", ft_strlen(": command not found\n"));
				exit(127);
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
	destroy_many_waitpid(pids, status, count);
	free(pids);
}

int gnacinq(t_shell* shell)
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
                    return -1;
				else if (shell->env_list->exit_code)
					return -1;
            }
            red = red->next;
        }
        cmd = cmd->next;
    }

    if (!shell->env_list->exit_code)
	{
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
	}
    return 0;
}