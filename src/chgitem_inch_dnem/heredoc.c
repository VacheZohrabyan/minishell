/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:55:19 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 18:05:06 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static void	handle_sigher(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
	exit(130);
}

static int	destroy_heredoc(pid_t pid, int status, int *pipefd,
		t_redirect *redirect)
{
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
	}
	signal(SIGINT, handle_sigher);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[1]);
	redirect->fd = pipefd[0];
	redirect->to = STDIN_FILENO;
	return (redirect->fd);
}

static void	message(t_redirect *redirect, int *pipefd)
{
	write(STDOUT_FILENO, "minishell: warning: here-document"
		" delimited by EOF (wanted `", ft_strlen("minishell:"
			" warning: here-document delimited by EOF (wanted `"));
	write(STDOUT_FILENO, redirect->file_name,
		ft_strlen(redirect->file_name));
	write(STDOUT_FILENO, "`)\n", ft_strlen("`)\n"));
	close(pipefd[1]);
	g_exit_status = 0;
	exit(0);
}

static void	heredoc_loop(t_redirect *redirect, int *pipefd, char *buffer)
{
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
			message(redirect, pipefd);
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

int	heredoc_file_open_wr(t_redirect *redirect)
{
	char	*buffer;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		buffer = NULL;
		heredoc_loop(redirect, pipefd, buffer);
		close(pipefd[1]);
	}
	else
		return (destroy_heredoc(pid, status, pipefd, redirect));
	return (0);
}
