/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:53:06 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/28 13:56:19 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	change_node_value(t_env_node **node, char *key, char *equal_sign)
{
	if (ft_strcmp(key, (*node)->key) == 0)
	{
		if ((*node)->is_equal)
		{
			if (equal_sign)
				(*node)->value = ft_strdup(equal_sign + 1);
			else
				(*node)->value = ft_strdup("");
			return (1);
		}
		if (equal_sign)
		{
			(*node)->value = ft_strdup(equal_sign + 1);
			(*node)->is_equal = 1;
		}
		else
		{
			(*node)->value = NULL;
			(*node)->is_equal = 0;
		}
		return (1);
	}
	return (0);
}
