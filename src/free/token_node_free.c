/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:36:50 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 17:52:07 by vzohraby         ###   ########.fr       */
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
		free(tmp->file_name);
		free(tmp);
	}
}
