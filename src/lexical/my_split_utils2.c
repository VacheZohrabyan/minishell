/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:53:41 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 13:19:59 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	**ft_free(char **res, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	*expend_env_function1(char *str, int *i,
	char *out, t_env_node *env)
{
	int		start;
	char	*name;
	char	*val;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	val = find_env(ft_strdup(name), env);
	out = ft_strjoin_gnl(out, val);
	free(name);
	return (out);
}

char	*expand_env(char *str, t_env_node *env)
{
	char	*out;
	int		i;
	char	*c;

	i = 0;
	out = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && str[i + 2] == '\0')
			return (ft_strjoin(out, "$?"));
		if (str[i] == '$')
			out = expend_env_function1(str, &i, out, env);
		else
		{
			c = (char *)malloc(sizeof(char) * 2);
			c[0] = str[i++];
			c[1] = '\0';
			out = ft_strjoin_gnl(out, c);
			free(c);
		}
	}
	free(str);
	return (out);
}

void	count_words_function1(char *s, int *i, char delim)
{
	char	q;

	while (s[*i] && s[*i] != delim)
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			q = s[(*i)++];
			while (s[*i] && s[*i] != q)
				(*i)++;
			if (s[*i] == q)
				(*i)++;
		}
		else
			(*i)++;
	}
}

int	count_words(char *s, char delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delim)
			i++;
		if (!s[i])
			break ;
		count++;
		count_words_function1(s, &i, delim);
	}
	return (count);
}
