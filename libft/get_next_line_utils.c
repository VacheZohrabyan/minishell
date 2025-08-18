/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:58:27 by zaleksan          #+#    #+#             */
/*   Updated: 2025/05/09 13:18:07 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *src)
{
	int	len;

	len = 0;
	if (!src)
		return (0);
	while (src[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
