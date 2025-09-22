// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredoc.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/20 18:55:19 by vzohraby          #+#    #+#             */
// /*   Updated: 2025/09/22 23:52:29 by vzohraby         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/include.h"

// // static void	handle_sigher(int sig)
// // {
// // 	(void)sig;
// // 	write(1, "\n", 1);
// // 	rl_on_new_line();
// // 	rl_replace_line("", 0);
// // 	rl_redisplay();
// // 	g_exit_status = 130;
// // }

// static int	destroy_heredoc(pid_t pid, int status, int *pipefd,
// 		t_redirect *redirect)
// {
// 	// signal(SIGINT, SIG_IGN);
// 	// signal(SIGQUIT, SIG_IGN);
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		g_exit_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 	{
// 		g_exit_status = 128 + WTERMSIG(status);
// 		if (WTERMSIG(status) == SIGINT)
// 			write(STDERR_FILENO, "\n", 1);
// 	}
// 	// signal(SIGINT, handle_sigher);
// 	// signal(SIGQUIT, SIG_IGN);
// 	if (g_exit_status != 0)
// 	{
// 		close(pipefd[0]);
// 		return (-1);
// 	}
// 	redirect->fd = pipefd[0];
// 	return (0);
// }

// static int	heredoc_loop(t_redirect *redirect, int *pipefd, char *buffer)
// {
// 	while (1)
// 	{
// 		buffer = readline("> ");
// 		if (!buffer)
// 		{
// 			write(STDOUT_FILENO, "minishell: warning: here-document"
// 				" delimited by EOF (wanted `", ft_strlen("minishell:"
// 					" warning: here-document delimited by EOF (wanted `"));
// 			write(STDOUT_FILENO, redirect->file_name,
// 				ft_strlen(redirect->file_name));
// 			write(STDOUT_FILENO, "`)\n", ft_strlen("`)\n"));
// 			close(pipefd[1]);
// 			exit(0);
// 		}
// 		if (ft_strcmp(redirect->file_name, buffer) == 0)
// 		{
// 			free(buffer);
// 			close(pipefd[1]);
// 			exit(0);	
// 		}
// 		write(pipefd[1], buffer, ft_strlen(buffer));
// 		write(pipefd[1], "\n", 1);
// 		free(buffer);
// 	}
// }

// int	heredoc_file_open_wr(t_redirect *redirect)
// {
// 	char	*buffer;
// 	int		pipefd[2];
// 	pid_t	pid;
// 	int		status;

// 	status = 0;
// 	if (pipe(pipefd) == -1)
// 		return (-1);
// 	pid = fork();
// 	if (pid < 0)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_IGN);
// 		close(pipefd[0]);
// 		buffer = NULL;
// 		heredoc_loop(redirect, pipefd, buffer);
// 	}
// 	close(pipefd[1]);
// 	return (destroy_heredoc(pid, status, pipefd, redirect));
// }

#include "../../inc/include.h"

static void	handle_sigher(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_exit_status = 130;
}

static void	heredoc_loop_child(t_redirect *redirect, int pipefd[2])
{
    char *buffer;

    while (1)
    {
        buffer = readline("> ");
        if (!buffer) // Ctrl+D / EOF
        {
            dprintf(STDOUT_FILENO,
                "minishell: warning: here-document delimited by EOF (wanted `%s`)\n",
                redirect->file_name);
            close(pipefd[1]);
            exit(0);
        }

        if (ft_strcmp(buffer, redirect->file_name) == 0)
        {
            free(buffer);
            close(pipefd[1]);
            exit(0); // child exits immediately
        }

        write(pipefd[1], buffer, ft_strlen(buffer));
        write(pipefd[1], "\n", 1);
        free(buffer);
    }
}

static int	destroy_heredoc(pid_t pid, int pipefd[2], t_redirect *redirect)
{
    int status;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);

    signal(SIGINT, handle_sigher);
    signal(SIGQUIT, SIG_IGN);

    if (g_exit_status != 0)
    {
        close(pipefd[0]);
        return (-1);
    }
	sig();
    redirect->fd = pipefd[0];
    return (0);
}

int	heredoc_file_open_wr(t_redirect *redirect)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return (-1);

    pid = fork();
    if (pid < 0)
        return (-1);

    if (pid == 0)
    {
        // Child process
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        close(pipefd[0]); // close read end
        heredoc_loop_child(redirect, pipefd);
    }

    // Parent process
    close(pipefd[1]); // close write end
    return destroy_heredoc(pid, pipefd, redirect);
}
