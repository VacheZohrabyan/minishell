/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 23:51:20 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	heredoc(t_command *cmd)
{
	t_redirect	*red;

	while (cmd)
	{
		red = cmd->redirect;
		while (red)
		{
			if (red->token_type == TOKEN_HEREDOC)
			{
				if (heredoc_file_open_wr(red) == -1)
				{
					// close(red->fd);
					return (1);
				}
			}
			if (red->fd > 0)
			{
				dup2(red->fd, STDIN_FILENO);	
				close(red->fd);
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
	if (heredoc(cmd) == -1)
	{
		// heredoc canceled, reset prompt state
		rl_clear_history();
		rl_replace_line("", 0);
		rl_on_new_line();
		return 1; // skip command execution
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
