/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:44:19 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 16:44:41 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static size_t	count_tokens(const char *s, char c)
{
	size_t	tokens;
	int		flag;

	tokens = 0;
	flag = 0;
	while (*s)
	{
		flag = 0;
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
		{
			if (!flag)
			{
				++tokens;
				flag = 1;
			}
			++s;
		}
	}
	return (tokens);
}

static char	*get_next_token(const char **s, char c)
{
	const char	*start;
	char		*token;

	while (**s && **s == c)
		++(*s);
	start = *s;
	while (**s && **s != c)
		++(*s);
	token = ft_substr(start, 0, *s - start);
	return (token);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	count;
	size_t	i;

	if (!s)
		return (NULL);
	count = count_tokens(s, c);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		arr[i] = get_next_token(&s, c);
		if (!arr[i])
		{
			ft_free(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
