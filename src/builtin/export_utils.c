/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:38:48 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/28 13:52:07 by zaleksan         ###   ########.fr       */
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
		if (head->is_equal && head->value != NULL)
		{
			write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
			write(STDOUT_FILENO, head->key, ft_strlen(head->key));
			write(STDOUT_FILENO, "=\"", ft_strlen("=\""));
			write(STDOUT_FILENO, head->value, ft_strlen(head->value));
			write(STDOUT_FILENO, "\"\n", ft_strlen("\"\n"));
		}
		else
		{
			write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
			write(STDOUT_FILENO, head->key, ft_strlen(head->key));
			write(STDOUT_FILENO, "\n", ft_strlen("\n"));
		}
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

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
