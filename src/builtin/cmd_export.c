/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:31:44 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/13 16:44:20 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

void	swap_env_nodes(t_env_node *a, t_env_node *b)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_equal;

	tmp_key = a->key;
	tmp_value = a->value;
	tmp_equal = a->is_equal;
	a->key = b->key;
	a->value = b->value;
	a->is_equal = b->is_equal;
	b->key = tmp_key;
	b->value = tmp_value;
	b->is_equal = tmp_equal;
}

void	sort_export(t_env_node *head)
{
	int			swapped;
	t_env_node	*current;
	t_env_node	*last;

	if (!head)
		return ;
	last = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current->next != last)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_env_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

void	print_export(t_env_node *head)
{
	while (head)
	{
		if (head->is_equal)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

char	*get_key(char *arg)
{
	size_t	key_size;
	size_t	i;
	char	*key;

	key_size = 0;
	while (arg[key_size] && arg[key_size] != '=')
		++key_size;
	key = (char *)malloc(sizeof(char) * (key_size + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_size)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	add_or_update_env(t_env *env, char *arg)
{
	size_t		i;
	t_env_node	*node;
	char		*equal_sign;
	char		*key;

	i = 0;
	if (!env || !arg)
		return ;
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return ;
	node = env->env_head;
	while (node)
	{
		key = get_key(arg);
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

int	cmd_export(t_shell *shell, t_command *command)
{
	int	i;

	i = 1;
	if (!command->argv[1])
	{
		sort_export(shell->export_list->env_head);
		print_export(shell->export_list->env_head);
		return (1);
	}
	while (command->argv[i])
	{
		add_or_update_env(shell->env_list, command->argv[i]);
		i++;
	}
	return (0);
}
