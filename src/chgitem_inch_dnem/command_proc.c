/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:57:38 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/28 14:51:05 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	pid_equal_zero(t_shell *shell, t_command *com)
{
	char	*str;

	signal(SIGQUIT, SIG_DFL);
	str = "";
	if (com->argv && com->argv[0])
		str = find_command_path(shell->env_list, com->argv[0],
				&(shell->status));
	if (com->redirect && any(com->redirect) == -1)
	{
		if (str)
			free(str);
		return ;
	}
	check_redirect(com);
	if (str && com->argv)
	{
		execv_function(shell, str, com, 1);
		free(str);
		str = NULL;
	}
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
}

void	command_proc(t_shell *shell, t_command *com)
{
	pid_t		pid;
	int			saved_stdout;

	if (check_builtin(shell, com))
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (com->redirect && any(com->redirect) == -1)
			return ;
		check_redirect(com);
		builtin_with_forks(shell, com);
		builtin_without_forks(shell, com);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return ;
	}
	sig();
	pid = fork();
	if (pid < 0)
		return (write (STDERR_FILENO, "error fork()\n",
				ft_strlen("error fork()\n")), (void)0);
	else if (pid == 0)
		pid_equal_zero(shell, com);
	else
		destroy_one_waitpid(pid, shell);
}
