#include "../../inc/builtin.h"

int	load_history(t_shell *shell)
{
	int		fd;
	char	*line;
	size_t	len;

	len = 0;
	fd = open(shell->history, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: history");
		return (-1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line)
			add_history(line);
		free(line);
	}
	close(fd);
	return (0);
}

int	init_shell_history(t_shell *shell)
{
	if (!shell || !shell->history)
		return (-1);
	shell->history_fd = open(shell->history, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (shell->history_fd == -1)
	{
		perror("minishell: history");
		return (-1);
	}
	return (0);
}

void	close_shell_history(t_shell *shell)
{
	if (shell->history_fd != -1)
		close(shell->history_fd);
	shell->history_fd = -1;
}

int	record_history(t_shell *shell, const char *line)
{
	add_history(shell->buffer);
	if (!shell || !line || !*line || shell->history_fd == -1)
		return (-1);
	if (write(shell->history_fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(shell->history_fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

int	history_c(t_shell *shell)
{
	int	fd;

	if (!shell->command->argv)
		return (0);
	if (!ft_strcmp("-c", shell->command->argv[1]))
	{
		fd = open(shell->history, O_TRUNC | O_WRONLY, 0644);
		if (fd != -1)
			close(fd);
		rl_clear_history();
		return (1);
	}
	return (0);
}

int	print_history(t_shell *shell)
{
	int		fd;
	char	*line;
	int		n;

	n = 1;
	fd = open(shell->history, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: history");
		return (-1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("   %d  %s", n++, line);
		free(line);
	}
	close(fd);
	return (1);
}

int	cmd_history(t_shell *shell)
{
	if (!shell || !shell->history)
	{
		printf("minishell: history file not set\n");
		return (-1);
	}
	if (!shell->command->argv[1])
		return (print_history(shell), 1);
	if (history_c(shell) || check_argument(shell->command, "history"))
		return (printf("hist\n"), -1);
	return (1);
}
