/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:00:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 19:34:17 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	execv_function(char *str, t_command *com, int flag)
{
	if (execv(str, com->argv) == -1)
	{
		free(str);
		write(STDOUT_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDOUT_FILENO, com->argv[0], ft_strlen(com->argv[0]));
		write(STDOUT_FILENO, ": command not found\n",
			ft_strlen(": command not found\n"));
		close(com->redirect->fd);
		g_exit_status = 127;
		if (flag)
			return ;
		else
			exit(127);
	}
}

void	check_redirect(t_command *com)
{
	t_redirect	*r;

	r = com->redirect;
	while (r)
	{
		if (r->fd != -1)
		{
			if (dup2(r->fd, r->to) == -1)
			{
				g_exit_status = 1;
				return ;
			}
			close(r->fd);
		}
	}
}
