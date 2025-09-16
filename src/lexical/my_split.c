/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/16 10:06:07 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

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
			char q = *(s);
			len = 0;
            
			while (s[len + 1] && s[len + 1] != q)
				len++;
			part = ft_substr(s, 0, len + 2);
			s += (len + 1);
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

char *remove_quotes(const char *str)
{
    char *out = ft_strdup("");
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            char q = str[i++];
            while (str[i] && str[i] != q)
            {
                char c[2] = {str[i], '\0'};
                out = ft_strjoin_gnl(out, ft_strdup(c));
                i++;
            }
            if (str[i] == q)
                i++;
        }
        else
        {
            char c[2] = {str[i], '\0'};
            out = ft_strjoin_gnl(out, ft_strdup(c));
            i++;
        }
    }
    return out;
}

char *find_env(char *res, t_env_node *env)
{
    t_env_node* tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, res) == 0)
		{
			free(res);
			res = NULL;
			return ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	free(res);
	res = NULL;
	return ft_strdup("");
}

char *expand_env(const char *str, t_env_node *env)
{
    char *out = ft_strdup("");
    int i = 0;

    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            int start = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;
            char *name = ft_substr(str, start, i - start);
            char *val = find_env(ft_strdup(name), env);
            out = ft_strjoin_gnl(out, val);
            free(name);
        }
        else
        {
            char c[2] = {str[i], '\0'};
            out = ft_strjoin_gnl(out, ft_strdup(c));
            i++;
        }
    }
    return out;
}

char *extract_quotes(char *res, t_env_node *env)
{
    size_t len = ft_strlen(res);

    if (len >= 2 && res[0] == '"' && res[len - 1] == '"')
    {
        char *inside = ft_substr(res, 1, len - 2);
        char *expanded = expand_env(inside, env);
        free(inside);
        free(res);
        return remove_quotes(expanded);
    }
    else if (len >= 2 && res[0] == '\'' && res[len - 1] == '\'')
    {
        char *inside = ft_substr(res, 1, len - 2);
        free(res);
        return remove_quotes(inside);
    }
    else
    {
        char *expanded = expand_env(res, env);
        free(res);
        return remove_quotes(expanded);
    }
}
char **my_split(const char *s, t_env_node* env, char delim)
{
	char **res;
	int words;
	int i = 0;
    (void)env;
    if (!s)
		return (NULL);
	words = count_words(s, delim);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < words)
	{
		res[i] = extract_word(&s, delim);
        res[i] = extract_quotes(res[i], env);
		if (!res[i])
			return (ft_free(res, i));
		i++;
	}
	res[i] = NULL;
	return (res);
}
