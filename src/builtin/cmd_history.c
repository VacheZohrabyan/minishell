#include "../../inc/builtin.h"

int	load_history(t_shell *shell)
{
	int	fd;
	char *line;

	fd = open(shell->history, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: history");
		return (-1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
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

int	cmd_history(t_shell *shell)
{
	int		fd;
	char	*line;
	int		n;

	if (!shell || !shell->history)
	{
		printf("minishell: history file not set\n");
		return (-1);
	}
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
