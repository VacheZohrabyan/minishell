/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/21 15:51:21 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	gnacinq(t_shell *shell)
{
	t_command	*tmp;
	t_command	*cmd;
	t_redirect	*red;
	int			count;

	tmp = shell->command;
	cmd = tmp;
	count = 0;
	while (cmd)
	{
		red = cmd->redirect;
		while (red)
		{
			if (red->token_type == TOKEN_HEREDOC)
			{
				if (heredoc_file_open_wr(red) == -1)
					return (0);
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	cmd = tmp;
	while (cmd)
	{
		shell->cmd_count++;
		cmd = cmd->next;
	}
	if (count == 1)
		command_proc(shell, shell->command);
	else if (count > 1)
		command_many_proc(shell);
	return (0);
}
