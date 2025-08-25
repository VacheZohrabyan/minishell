/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:11:38 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/25 17:56:07 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == ';' || c == '(' || c == ')' || c == '&');
}

int	is_double_special(const char *buffer, size_t i)
{
	return (
		(buffer[i] == '<' && buffer[i + 1] == '<')
		|| (buffer[i] == '>' && buffer[i + 1] == '>')
	);
}
