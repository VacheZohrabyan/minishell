/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:31:44 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/22 13:14:10 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

void	add_or_update_env(t_env *env, char *arg)
{
	t_env_node	*node;
	char		*equal_sign;
	char		*key;

	if (!env || !arg)
		return ;
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return ;
	node = env->env_head;
	key = get_key(arg);
	while (node)
	{
		if (equal_sign && ft_strcmp(key, node->key) == 0)
		{
			free(node->value);
			node->value = ft_strdup(equal_sign + 1);
			node->is_equal = 1;
			free(key);
			return ;
		}
		node = node->next;
	}
	free(key);
	push_back(&env->env_head, arg);
}

int	update_node(t_env_node *node, char *arg, char *key)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	while (node)
	{
		if (ft_strcmp(key, node->key) == 0)
		{
			free(node->value);
			if (equal_sign)
			{
				node->value = ft_strdup(equal_sign + 1);
				node->is_equal = 1;
			}
			else
			{
				node->value = NULL;
				node->is_equal = 0;
			}
			free(key);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void	add_or_update_export(t_shell *shell, char *arg)
{
	t_env_node	*node;
	char		*key;

	key = get_key(arg);
	if (!shell->export_list || !arg)
		return ;
	node = shell->export_list->env_head;
	if (update_node(node, arg, key))
		return ;
	push_back(&(shell->export_list)->env_head, arg);
	free(key);
}

void	print_error(t_command *command, int i)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, command->argv[i], ft_strlen(command->argv[i]));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	g_exit_status = 1;
}

int	cmd_export(t_shell *shell, t_command *command)
{
	int	i;

	i = 1;
	if (!command->argv[1])
	{
		sort_export(shell->export_list->env_head);
		print_export(shell->export_list->env_head);
		g_exit_status = 0;
		return (0);
	}
	while (command->argv[i])
	{
		if (!is_valid_identifier(command->argv[i]))
			print_error(command, i);
		else
		{
			add_or_update_env(shell->env_list, command->argv[i]);
			add_or_update_export(shell, command->argv[i]);
			g_exit_status = 0;
		}
		i++;
	}
	return (0);
}
