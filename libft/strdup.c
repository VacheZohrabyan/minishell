/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:57:53 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 16:44:45 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	s_len = ft_strlen(s1);
	ptr = (char *)malloc((s_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
