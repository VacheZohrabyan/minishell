/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/11 09:58:02 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/10 23:50:00 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char **ft_free(char **res, int size)
{
	int i = 0;
	while (i < size)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char *append_and_free(char *acc, char *part)
{
	char *new;

	if (!part)
		return (acc);
	if (!acc)
		new = ft_strdup(part);
	else
	{
		new = ft_strjoin(acc, part);
		free(acc);
	}
	free(part);
	return (new);
}

static int count_words(const char *s, char delim)
{
	int i = 0;
	int count = 0;

	while (s[i])
	{
		while (s[i] && s[i] == delim)
			i++;
		if (!s[i])
			break;
		count++;
		while (s[i] && s[i] != delim)
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				char q = s[i++];
				while (s[i] && s[i] != q)
					i++;
				if (s[i] == q)
					i++;
			}
			else
				i++;
		}
	}
	return (count);
}

static char *extract_word(const char **ps, char delim)
{
	const char *s = *ps;
	char *acc = NULL;
	char *part;
	int len;

	while (*s && *s == delim)
		s++;
	while (*s && *s != delim)
	{
		if (*s == '\'' || *s == '"')
		{
			char q = *s++;
			len = 0;
			while (s[len] && s[len] != q)
				len++;
			part = ft_substr(s, 0, len);
			s += len;
			if (*s == q)
				s++;
			acc = append_and_free(acc, part);
		}
		else
		{
			len = 0;
			while (s[len] && s[len] != delim && s[len] != '\'' && s[len] != '"')
				len++;
			part = ft_substr(s, 0, len);
			s += len;
			acc = append_and_free(acc, part);
		}
	}
	*ps = s;
	if (!acc)
		acc = ft_strdup("");
	return (acc);
}

char **my_split(const char *s, char delim)
{
	char **res;
	int words;
	int i = 0;

	if (!s)
		return (NULL);
	words = count_words(s, delim);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < words)
	{
		res[i] = extract_word(&s, delim);
		if (!res[i])
			return (ft_free(res, i));
		i++;
	}
	res[i] = NULL;
	return (res);
}
