/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:36:50 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/23 14:56:57 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	token_node_free(t_token **token)
{
	t_token	*tmp;

	if (!*token)
		return ;
	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp->cmd);
		free(tmp);
	}
}
