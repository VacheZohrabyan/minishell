/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 15:25:31 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	heredoc(t_command *cmd)
{
	t_redirect	*red;
	int			fd;

	while (cmd)
	{
		red = cmd->redirect;
		while (red)
		{
			if (red->token_type == TOKEN_HEREDOC)
			{
				fd = heredoc_file_open_wr(red);
				if (fd < 0)
					return (1);
				else
					red->fd = fd;
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	gnacinq(t_shell *shell)
{
	t_command	*tmp;
	t_command	*cmd;

	tmp = shell->command;
	cmd = tmp;
	shell->cmd_count = 0;
	if (heredoc(cmd))
	{
		g_exit_status = 0;
		return (0);
	}
	cmd = tmp;
	while (cmd)
	{
		shell->cmd_count++;
		cmd = cmd->next;
	}
	if (shell->cmd_count == 1)
		command_proc(shell, shell->command);
	else if (shell->cmd_count > 1)
		command_many_proc(shell);
	return (0);
}
