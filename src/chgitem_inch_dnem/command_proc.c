/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:57:38 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/21 16:07:54 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"


void pid_equal_zero(t_shell* shell, t_command* com)
{
	char* str;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	str = find_command_path(shell->env_list, com->argv[0]);
	check_redirect(com);
	execv_function(str, com, 1);
	close(com->redirect->fd);
	free(str);
}

void	command_proc(t_shell *shell, t_command *com)
{
	pid_t		pid;
	int			status;
	int			saved_stdout;
	if (check_builtin(shell, com))
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (com->redirect && any(com->redirect) != -1)
			check_redirect(com);
		builtin_with_forks(shell, com);
		builtin_without_forks(shell, com);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return ;
	}
	pid = fork();
	status = 0;
	if (pid < 0)
		return (write (STDOUT_FILENO, "error fork()\n",
			ft_strlen("error fork()\n")), (void)0);
	else if (pid == 0)
		pid_equal_zero(shell, com);
	else
		destroy_one_waitpid(pid, status);
}
