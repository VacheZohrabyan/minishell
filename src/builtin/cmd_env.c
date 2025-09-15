/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:47:00 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/15 17:47:02 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	cmd_env(t_env *env)
{
	size_t		i;
	t_env_node	*current;

	i = 0;
	if (!env)
		return (0);
	current = env->env_head;
	while (current)
	{
		if (current->is_equal && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}
