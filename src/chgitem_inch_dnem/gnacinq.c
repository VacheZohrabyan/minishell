/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 11:42:38 by vzohraby         ###   ########.fr       */
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
					return (1);
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
		return (0);
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
