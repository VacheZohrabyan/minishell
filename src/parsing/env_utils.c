/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:10 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/30 15:35:11 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	*get_env_param(t_env *env, char *key)
{
	size_t		i;
	t_env_node	*node;

	if (!env || !key)
		return (NULL);
	i = 0;
	while (env->buffer_env[i])
	{
		node = env->buffer_env[i];
		while (node)
		{
			if (ft_strcmp(key, node->key) == 0)
				return (node->value);
			node = node->next;
		}
		i++;
	}
	return (NULL);
}