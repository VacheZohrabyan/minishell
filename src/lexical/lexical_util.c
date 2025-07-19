/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:11:38 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/19 15:12:01 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexical.h"

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
		|| (buffer[i] == '|' && buffer[i + 1] == '|')
		|| (buffer[i] == '&' && buffer[i + 1] == '&')
	);
}
