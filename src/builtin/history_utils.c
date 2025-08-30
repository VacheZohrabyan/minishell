/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:04:24 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/30 19:08:06 by zaleksan         ###   ########.fr       */
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
		printf("   %d  %s", n++, line);
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
