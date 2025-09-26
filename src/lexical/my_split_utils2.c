/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:53:41 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 18:22:44 by vzohraby         ###   ########.fr       */
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

char	*expend_env_function1(char *str, int *i, char *out, t_env_node *env)
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

char	*expand_env(char *str, t_env_node *env, int *status)
{
	char	*out;
	int		i;

	i = 0;
	out = NULL;
	if (str[0] == '$' && str[1] == '\0')
		return (ft_strdup("$"));
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			*status = 0;
			out = expend_env_function2(str, out, &i);
		}
		else if (str[i] == '$')
			out = expend_env_function1(str, &i, out, env);
		else
		{
			*status = 0;
			out = append_char(out, str[i++]);
		}
	}
	return (free(str), out);
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
