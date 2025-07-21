/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:35:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 17:52:14 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	free_env_node(t_env_node *node)
{
	t_env_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}
}

void	free_env(t_env *env)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	if (env->buffer_env)
	{
		while (i < MAX_SIZE_ENV)
		{
			if (env->buffer_env[i])
				free_env_node(env->buffer_env[i]);
			++i;
		}
		free(env->buffer_env);
	}
	free(env);
}
