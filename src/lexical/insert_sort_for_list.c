/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort_for_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:35:02 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 17:52:02 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	insert_sort_for_list(t_token *token)
{
	t_token	*temp;
	t_token	*tmp;
	t_token	*current;

	temp = token;
	current = token;
	while (current)
	{
		temp = current;
		while (temp)
			;
		current = current->next;
	}
}
