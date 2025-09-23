/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:00:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/23 21:03:24 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	execv_function(char *str, t_command *com, int flag)
{
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	if (execve(str, com->argv, NULL) == -1)
	{
		if (ft_strcmp(com->argv[0], "$?") == 0)
		{
			free(str);
			write(STDERR_FILENO, ": command not found\n",
				ft_strlen(": command not found\n"));
			exit(127);
		}
		free(str);
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDERR_FILENO, com->argv[0], ft_strlen(com->argv[0]));
		write(STDERR_FILENO, ": command not found\n",
			ft_strlen(": command not found\n"));
		close(com->redirect->fd);
		g_exit_status = 127;
		exit(127);
		(void)flag;
	}
	g_exit_status = 0;
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
			}
			close(r->fd);
		}
		r = r->next;
	}
}
