/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:35:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/17 14:51:21 by vzohraby         ###   ########.fr       */
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
