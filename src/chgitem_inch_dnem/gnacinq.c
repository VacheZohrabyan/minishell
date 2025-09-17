/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/17 15:42:11 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	heredoc_file_open_wr(t_redirect *redirect)
{
	char	*buffer;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, handle_sigint);
		while (1)
		{
			buffer = readline("> ");
			if (!buffer)
			{
				fprintf(stderr,
					"minishell: warning: here-document delimited by EOF (wanted `%s`)\n",
					redirect->file_name);
				close(pipefd[1]);
				exit(0);
			}
			if (ft_strcmp(redirect->file_name, buffer) == 0)
			{
				free(buffer);
				close(pipefd[1]);
				g_exit_status = 0;
				exit(0);
			}
			write(pipefd[1], buffer, ft_strlen(buffer));
			write(pipefd[1], "\n", 1);
			free(buffer);
		}
	}
	else
	{
		close(pipefd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		g_exit_status = status % 255;
		signal(SIGINT, handle_sigher);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			g_exit_status = WEXITSTATUS(status);
			close(pipefd[0]);
			return (-1);
		}
		redirect->fd = pipefd[0];
	}
	return (0);
}

int	any(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN) // <
		{
			tmp->fd = open(tmp->file_name, O_RDONLY);
			if (tmp->fd == -1)
			{
				write(2, "minishell: ", 11);
				perror(tmp->file_name);
				g_exit_status = 1;
				return (-1);
			}
			tmp->to = STDIN_FILENO;
		}
		else if (tmp->token_type == TOKEN_REDIRECT_OUT) //>
		{
			tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (tmp->fd == -1)
			{
				if (access(tmp->file_name, W_OK) == -1)
					write(2, "minishell: Permission denied\n", 29);
				else
				{
					write(2, "minishell: ", 11);
					perror(tmp->file_name);
				}
				g_exit_status = 1;
				return (-1);
			}
			tmp->to = STDOUT_FILENO;
		}
		else if (tmp->token_type == TOKEN_REDIRECT_APPEND) // >>
		{
			tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp->fd == -1)
			{
				if (access(tmp->file_name, W_OK) == -1)
					write(2, "minishell: Permission denied\n", 29);
				else
				{
					write(2, "minishell: ", 11);
					perror(tmp->file_name);
				}
				g_exit_status = 1;
				return (-1);
			}
			tmp->to = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	absolute_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	return (0);
}

char	*find_command_path(t_env *env, char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;
	char	*tmp;
	int		j;

	if (absolute_path(cmd))
		return (ft_strdup(cmd));
	path_env = get_env_param(env, "PATH", 1);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			j = 0;
			while (paths[j])
				free(paths[j++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
	return (NULL);
}

void	command_proc(t_shell *shell, t_command *com)
{
	pid_t		pid;
	int			status;
	char		*str;
	t_redirect* r;
	if (check_builtin(shell, com))
		return ;
	pid = fork();
	status = 0;
	signal(SIGINT, handle_sigcat);
	if (pid < 0)
	{
		printf("error fork()\n");
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		str = find_command_path(shell->env_list, com->argv[0]);
		if (com->redirect)
		{
			if (any(com->redirect) == -1)
				exit(1);
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
		if (execv(str, com->argv) == -1)
		{
			free(str);
			write(2, "minishell: ", ft_strlen("minishell: "));
			write(2, com->argv[0], ft_strlen(com->argv[0]));
			write(2, ": command not found\n",
				ft_strlen(": command not found\n"));
			close(com->redirect->fd);
			return ;
		}
		close(com->redirect->fd);
		free(str);
	}
	else
		destroy_one_waitpid(pid, status);
}

void	command_many_proc(t_shell *shell, int count)
{
	int			**pipe_fd;
	t_command	*tmp;
	pid_t		*pids;
	int			status;
	int			i;
	pid_t		pid;
	t_redirect	*red;
	char		*str;
	int			j;
	t_redirect	*r;

	tmp = shell->command;
	status = 0;
	pipe_fd = (int **)malloc(sizeof(int *) * (count - 1));
	if (!pipe_fd)
		return ;
	pids = (pid_t *)malloc(sizeof(pid_t) * count);
	i = 0;
	if (count > 1)
	{
		while (i < count - 1)
		{
			pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
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
				return ;
			}
			++i;
		}
	}
	i = 0;
	while (tmp && i < count)
	{
		if (count == 1 && check_builtin(shell, tmp))
			return ;
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
				r = red;
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
			str = find_command_path(shell->env_list, tmp->argv[0]);
			if (execv(str, tmp->argv) == -1)
			{
				write(2, "minishell: ", ft_strlen("minishell: "));
				write(2, tmp->argv[0], ft_strlen(tmp->argv[0]));
				write(2, ": command not found\n",
					ft_strlen(": command not found\n"));
				exit(127);
			}
			free(str);
		}
		else
			pids[i] = pid;
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
	free(pipe_fd);
	i = 0;
	destroy_many_waitpid(pids, status, count);
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
			printf("redirect = %d redirect_name = %s\n", red->token_type, red->file_name);
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