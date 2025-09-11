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

int	add_or_update_env(t_env *env, char *arg)
{
	size_t		i;
	size_t		env_size;
	t_env_node	*node;
	char		*equal_sign;

	i = 0;
	env_size = 0;
	if (!env || !arg)
		return (-1);
	equal_sign = ft_strchr(arg, '=');
	while (env->buffer_env[i])
	{
		node = env->buffer_env[i];
		while (node)
		{
			if (equal_sign && ft_strncmp(arg, node->key, (equal_sign
						- arg)) == 0)
			{
				free(node->value);
				node->value = ft_strdup(equal_sign + 1);
				node->is_equal = 1;
				return (0);
			}
			else if (!equal_sign && ft_strcmp(arg, node->key) == 0)
			{
				node->is_equal = 0;
				return (1);
			}
			node = node->next;
		}
		i++;
		env_size++;
	}
	push_back(&env->buffer_env[0], arg);
	return (0);
}

int	cmd_export(t_shell *shell, t_command *command)
{
	int	i;

	i = 1;
	if (!command->argv[1])
	{
		sort_export(shell->export_list->buffer_env[0]);
		print_export(shell->export_list->buffer_env[0]);
		return (1);
	}
	while (command->argv[i])
	{
		if (add_or_update_env(shell->env_list, command->argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}
