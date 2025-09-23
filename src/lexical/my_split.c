/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/23 19:45:13 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	*remove_quotes_function2(char *str, char *out, char *c, int *i)
{
	char	q;

	q = str[(*i)++];
	while (str[*i] && str[*i] != q)
	{
		c = (char *)malloc(sizeof(char) * 2);
		c[0] = str[*i];
		c[1] = '\0';
		out = ft_strjoin_gnl(out, ft_strdup(c));
		(*i)++;
		free(c);
		c = NULL;
	}
	if (str[*i] == q)
		(*i)++;
	return (out);
}

char	*append_and_free(char *acc, char *part)
{
	char	*new;

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

char	*find_env(char *res, t_env_node *env)
{
	t_env_node	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, res) == 0)
		{
			free(res);
			res = NULL;
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(res);
	res = NULL;
	return (ft_strdup(""));
}

char	*extract_quotes(char *res, t_env_node *env)
{
	size_t	len;
	char	*expanded;
	char	*inside;

	len = ft_strlen(res);
	if (len >= 2 && res[0] == '"')
	{
		inside = ft_substr(res, 1, len - 2);
		expanded = expand_env(inside, env);
		free(res);
		return (expanded);
	}
	else if (len >= 2 && res[0] == '\'')
	{
		inside = ft_substr(res, 1, len - 2);
		free(res);
		return (inside);
	}
	else
	{
		expanded = expand_env(res, env);
		free(res);
		return (remove_quotes(expanded));
	}
}

char	**my_split(char *s, t_env_node *env, char delim)
{
	char	**res;
	int		words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	words = count_words(s, delim);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < words)
	{
		res[i] = extract_word(&s, env, delim);
		if (!res[i])
			return (ft_free(res, i));
		i++;
	}
	res[i] = NULL;
	return (res);
}
