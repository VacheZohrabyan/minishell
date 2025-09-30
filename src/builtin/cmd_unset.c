/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:31:38 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/30 12:37:59 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	delete_env_node(t_env_node **head, char *key)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!head || !*head || !key)
		return (1);
	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	unset_env(t_env *env, char *key)
{
	if (!env || !key)
		return (1);
	if (!delete_env_node(&env->env_head, key))
		return (0);
	return (1);
}

int	cmd_unset(t_shell *shell, t_command *command)
{
	int	i;

	i = 1;
	if (!command->argv[1])
		return (0);
	while (command->argv[i])
	{
		unset_env(shell->env_list, command->argv[i]);
		unset_env(shell->export_list, command->argv[i]);
		i++;
	}
	g_exit_status = 0;
	return (1);
}
