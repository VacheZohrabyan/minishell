/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/10 10:35:51 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(const char *s, char c)
{
	int i = 0;
	int count = 0;

	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break;
		count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			char quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
		{
			while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '"')
				i++;
		}
	}
	return (count);
}

static void *ft_free(char **res, int size)
{ 
	int i; 
	i = 0; 
	while (i < size) 
	{ 
		free(res[i]); 
		i++; 
	} 
	free(res); 
	return (NULL); 
}

static char	*extract_word(const char **s, char c)
{
	char	*word;
	int		len = 0;
	char	quote;

	while (**s == c)
		(*s)++;
	if (**s == '\'' || **s == '"')
	{
		quote = *(*s)++;
		while ((*s)[len] && (*s)[len] != quote)
			len++;
		word = ft_substr(*s, 0, len);
		if ((*s)[len] == quote)
			len++;
		*s += len;
	}
	else
	{
		while ((*s)[len] && (*s)[len] != c && (*s)[len] != '\'' && (*s)[len] != '"')
			len++;
		word = ft_substr(*s, 0, len);
		*s += len;
	}
	return (word);
}

char	**my_split(const char *s, char c)
{
	char	**res;
	int		words;
	int		i = 0;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < words)
	{
		res[i] = extract_word(&s, c);
		if (!res[i])
			return (ft_free(res, i));
		i++;
	}
	res[i] = NULL;
	i = 0;
	words = 0;
	return (res);
}