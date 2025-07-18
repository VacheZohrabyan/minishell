/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:35:07 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/18 22:29:49 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexical.h"

void	split_free(char ***buffer)
{
	size_t	i;

	i = 0;
	if (!buffer || !*buffer)
		return ;
	while ((*buffer)[i])
	{
		free((*buffer)[i]);
		i++;
	}
	free(*buffer);
	*buffer = NULL;
}
