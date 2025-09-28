/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/28 11:19:34 by vzohraby         ###   ########.fr       */
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
					return (-1);
				else
					red->fd = fd;
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	gnacinq(t_shell *shell)
{
	t_command	*tmp;
	t_command	*cmd;
	int			flag;
	tmp = shell->command;
	cmd = tmp;
	shell->cmd_count = 0;
	if (heredoc(cmd) == -1)
	{
		g_exit_status = 0;
		return (0);
	}
	cmd = tmp;
	flag = 0;
	while (cmd)
	{
		if (cmd->argv)
			flag = 1;
		shell->cmd_count++;
		cmd = cmd->next;
	}
	if (shell->cmd_count == 1 && flag)
		command_proc(shell, shell->command);
	else if (shell->cmd_count > 1 && flag)
		command_many_proc(shell);
	return (0);
}
