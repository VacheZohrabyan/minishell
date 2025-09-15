/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:30:50 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/15 18:01:24 by vzohraby         ###   ########.fr       */
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

char* find_env(char* res, t_env_node* env, int i)
{
    t_env_node* tmp = env;
	char* temp = NULL;
	char* word = NULL;
	size_t j = 0;
	int flag = 0;
	int count;
    while (tmp)
    {
		if (!flag)
		{
			while (temp[i] && temp[i] == ' ')
				++i;
			while (temp[j] && temp[j] != ' ')
				++j;
			word = (char*)malloc(sizeof(char) * (j + 1));
			while (temp[count] && temp[count])
			{
				word[count] = temp[count];
				count++;	
			}
			flag = 1;
		}
		if (ft_strcmp(tmp->key, word) == 0)
		{
			
			if (i > 1)
			{
				while (i-- != 0)
					temp = ft_strjoin_gnl(temp, " ");
			}
			temp = ft_strjoin_gnl(temp, tmp->value);
			flag = 0;
			free(word);
			word = NULL;
			count = 0;	
		}
		tmp = tmp->next;
    }
	return ft_strdup("");
}

char* extract_quotes(char* res, t_env_node* env)
{
    int i = 1;
    (void)env;
    if (res[0] == '"')
    {
		while (res[i] && res[i] == ' ')
			++i;
		char* tmp = res + i;
        if (res[i] == '$' && res[i + 1] != ' ')
        {
			tmp[ft_strlen(tmp) - 1] = '\0';
            tmp = find_env(tmp + 1, env, i);
			free(res);
			res = NULL;
            return tmp;
        }
		else 
		{
			tmp = res + 1;
			tmp[ft_strlen(tmp) - 1] = '\0';
			tmp = ft_strdup(tmp);
			free(res);
			res = NULL;
			return tmp;
		}
    }
	if (res[0] == '$')
	{
		if (res[1] == '\'' || res[1] == '"')
		{
			char* tmp = res + 2;
			printf("res = %s\n", tmp);
			tmp[ft_strlen(tmp) - 1] = '\0';
			tmp = ft_strdup(tmp);
			free(res);
			res = NULL;
			return tmp;
		}
	}        
	return res;
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
