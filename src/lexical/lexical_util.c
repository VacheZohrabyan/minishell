/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:11:38 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/23 19:56:22 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_double_special(const char *buffer, size_t i)
{
	return (
		(buffer[i] == '<' && buffer[i + 1] == '<')
		|| (buffer[i] == '>' && buffer[i + 1] == '>')
	);
}

char	*append_char(char *out, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	out = ft_strjoin_gnl(out, buf);
	return (out);
}
