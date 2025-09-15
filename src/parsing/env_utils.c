/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:10 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/15 17:40:12 by vzohraby         ###   ########.fr       */
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
	t_env_node *node;

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