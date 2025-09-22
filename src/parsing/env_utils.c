/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:10 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/22 12:14:03 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	*get_env_param(t_env *env, char *key, int flag)
{
	t_env_node	*node;

	if (!env || !key)
		return (NULL);
	node = env->env_head;
	while (node)
	{
		if (ft_strcmp(key, node->key) == 0)
		{
			if (flag == 1)
				return (node->value);
			else
				return (node->key);
		}
		node = node->next;
	}
	return (NULL);
}

int	set_env_param(t_env *env, char *key, char *value)
{
	t_env_node	*node;

	if (!env || !key)
		return (0);
	node = env->env_head;
	while (node)
	{
		if (ft_strcmp(key, node->key) == 0)
		{
			free(node->value);
			node->value = value;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int	init_env_node_key(t_env_node *tmp, char *env, size_t *key_size)
{
	size_t	i;

	i = 0;
	*key_size = 0;
	while (env[*key_size] && env[*key_size] != '=')
		(*key_size)++;
	tmp->key = malloc(*key_size + 1);
	if (!tmp->key)
		return (-1);
	while (i < *key_size)
	{
		tmp->key[i] = env[i];
		i++;
	}
	tmp->key[i] = '\0';
	return (0);
}

void	shlvl(t_shell *shell)
{
	t_env_node	*env;

	env = shell->env_list->env_head;
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			free(env->value);
			env->value = ft_strdup("1");
			return ;
		}
		env = env->next;
	}
	return ;
}
