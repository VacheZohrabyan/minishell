/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:00:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/24 10:43:56 by vzohraby         ###   ########.fr       */
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

static void	handle_execve_error(t_command *com, char *str, char **env_array)
{
	if (ft_strcmp(com->argv[0], "$?") == 0)
	{
		if (com->redirect && com->redirect->fd >= 0)
			close(com->redirect->fd);
		free(str);
		free_split(env_array);
		write(STDERR_FILENO, ": command not found\n",
			ft_strlen(": command not found\n"));
		exit(127);
	}
	free(str);
	free_split(env_array);
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, com->argv[0], ft_strlen(com->argv[0]));
	write(STDERR_FILENO, ": command not found\n",
		ft_strlen(": command not found\n"));
	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	g_exit_status = 127;
	exit(127);
}

void	execv_function(t_shell *shell, char *str, t_command *com, int flag)
{
	char	**env_array;

	if (com->redirect && com->redirect->fd >= 0)
		close(com->redirect->fd);
	env_array = env_in_array(shell);
	if (execve(str, com->argv, env_array) == -1)
		handle_execve_error(com, str, env_array);
	free_split(env_array);
	g_exit_status = 0;
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
