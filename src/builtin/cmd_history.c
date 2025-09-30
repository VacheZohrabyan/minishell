/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:00:48 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/30 12:31:28 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line)
			add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	init_shell_history(t_shell *shell)
{
	if (!shell || !shell->history)
		exit(1);
	shell->history_fd = open(shell->history, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (shell->history_fd == -1)
	{
		perror("minishell: history");
		return (-1);
	}
	return (0);
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

int	check_argument(t_command *command)
{
	if (is_non_numeric(command->argv[1]) || !ft_atol(command->argv[1]))
	{
		ft_putstr_fd("minishell: history: ", STDERR_FILENO);
		ft_putstr_fd(command->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

int	cmd_history(t_shell *shell, t_command *command)
{
	if (!shell || !shell->history)
	{
		write(STDERR_FILENO, "minishell: history file not set\n",
			ft_strlen("minishell: history file not set\n"));
		return (-1);
	}
	if (!command->argv[1])
		return (print_history(shell), 1);
	if (history_c(shell) || check_argument(command))
		return (-1);
	return (1);
}
