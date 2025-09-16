/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:05:51 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 19:57:11 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

size_t	handle_double_special(const char *buffer,
		char *result, size_t i, size_t *j)
{
	if (*j > 0 && result[*j - 1] != ' ')
		result[(*j)++] = ' ';
	result[(*j)++] = buffer[i];
	result[(*j)++] = buffer[i + 1];
	i += 2;
	if (buffer[i] && buffer[i] != ' ')
		result[(*j)++] = ' ';
	return (i);
}

void	handle_single_special(const char *buffer,
			char *result, size_t i, size_t *j)
{
	if (*j > 0 && result[*j - 1] != ' ')
		result[(*j)++] = ' ';
	result[(*j)++] = buffer[i];
	if (buffer[i + 1] && buffer[i + 1] != ' ')
		result[(*j)++] = ' ';
}

int	dispatch_special_handler(const char *buffer,
	char *result, size_t *i, size_t *j)
{
	if (is_double_special(buffer, *i))
	{
		*i = handle_double_special(buffer, result, *i, j);
		return (1);
	}
	if (is_special(buffer[*i]))
	{
		handle_single_special(buffer, result, *i, j);
		(*i)++;
		return (1);
	}
	return (0);
}

char	*add_spaces_around_specials(const char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*result;

	i = 0;
	j = 0;
	len = ft_strlen(buffer);
	result = malloc(len * 3 + 1);
	if (!result)
		return (NULL);
	while (buffer[i])
	{
		if (dispatch_special_handler(buffer, result, &i, &j))
			continue ;
		result[j++] = buffer[i++];
	}
	result[j] = '\0';
	return (result);
}
