/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:00:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/28 11:06:19 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	count_env(t_env_node *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_in_array(t_shell *shell)
{
	int			count;
	t_env_node	*env;
	char		**env_array;
	int			i;

	env = shell->env_list->env_head;
	count = count_env(env);
	env = shell->env_list->env_head;
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env && i < count)
	{
		env_array[i] = ft_strdup("");
		env_array[i] = ft_strjoin_gnl(env_array[i], env->key);
		env_array[i] = ft_strjoin_gnl(env_array[i], "=");
		env_array[i] = ft_strjoin_gnl(env_array[i], env->value);
		++i;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

static void	handle_execve_error(t_shell *shell, t_command *com,
		char **env_array)
{
	if (shell->status == 2)
		message_no_such_file(com, env_array);
	if (shell->status == 1)
		message_permission_denied(com, env_array);
	if (com->argv && com->argv[0])
		message_command_not_fount(com, env_array);
	g_exit_status = 0;
	exit (g_exit_status);
}

void	execv_function(t_shell *shell, char *str, t_command *com, int flag)
{
	char	**env_array;

	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	env_array = env_in_array(shell);
	if (execve(str, com->argv, env_array) == -1)
		handle_execve_error(shell, com, env_array);
	free_split(env_array);
	(void)flag;
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
