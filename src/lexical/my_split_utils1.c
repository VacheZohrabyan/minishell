/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:51:14 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/18 15:52:20 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	*extract_word_function1(char **s, t_env_node *env)
{
	char	q;
	int		len;
	char	*part;

	q = **s;
	len = 1;
	while ((*s)[len] && (*s)[len] != q)
		len++;
	part = ft_substr(*s, 0, len + 1);
	*s += len;
	if (**s == q)
	{
		part = extract_quotes(part, env);
		(*s)++;
	}
	return (part);
}

char	*extract_word_function2(char **s, t_env_node *env, char delim)
{
	int		len;
	char	*part;

	len = 0;
	while ((*s)[len] && (*s)[len] != delim &&
		(*s)[len] != '\'' && (*s)[len] != '"')
		len++;
	part = ft_substr(*s, 0, len);
	*s += len;
	part = expand_env(part, env);
	return (part);
}

char	*extract_word(char **ps, t_env_node *env, char delim)
{
	char	*s;
	char	*acc;
	char	*part;

	s = *ps;
	acc = NULL;
	while (*s && *s == delim)
		s++;
	while (*s && *s != delim)
	{
		if (*s == '\'' || *s == '"')
			part = extract_word_function1(&s, env);
		else
			part = extract_word_function2(&s, env, delim);
		acc = append_and_free(acc, part);
	}
	*ps = s;
	if (!acc)
		acc = ft_strdup("");
	return (acc);
}

char	*remove_quotes_function1(char *str, char *out, char *c, int *i)
{
	c = (char *)malloc(sizeof(char) * 2);
	c[0] = str[*i];
	c[1] = '\0';
	out = ft_strjoin_gnl(out, ft_strdup(c));
	free(c);
	c = NULL;
	(*i)++;
	return (out);
}

char	*remove_quotes(char *str)
{
	char	*out;
	int		i;
	char	*c;

	out = ft_strdup("");
	c = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			out = remove_quotes_function2(str, out, c, &i);
		else
			out = remove_quotes_function1(str, out, c, &i);
	}
	free(str);
	str = NULL;
	return (out);
}
