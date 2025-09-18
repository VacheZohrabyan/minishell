/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:24 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/18 16:23:47 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

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
	line = get_next_line(fd);
	while (line != NULL)
	{
		write (STDOUT_FILENO, "   ", ft_strlen("   "));
		write (STDOUT_FILENO, ft_itoa(n), ft_strlen(ft_itoa(n)));
		n++;
		write (STDOUT_FILENO, "  ", ft_strlen("  "));
		write (STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	close_shell_history(t_shell *shell)
{
	if (shell->history_fd != -1)
		close(shell->history_fd);
	shell->history_fd = -1;
}
