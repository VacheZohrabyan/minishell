/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/19 14:23:37 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexical.h"

t_token_type	check_token_type(char *buffer)
{
	if (buffer[0] == '|' && buffer[1] != '|')
		return (TOKEN_PIPE);
	else if (buffer[0] == '|' && buffer[1] == '|')
		return (TOKEN_OR);
	else if (buffer[0] == '&' && buffer[1] == '&')
		return (TOKEN_AND);
	else if (buffer[0] == '(')
		return (TOKEN_OPEN);
	else if (buffer[0] == ')')
		return (TOKEN_CLOSE);
	else if (buffer[0] == '<' && buffer[1] != '<')
		return (TOKEN_REDIRECT_IN);
	else if (buffer[0] == '<' && buffer[1] == '<')
		return (TOKEN_HEREDOC);
	else if (buffer[0] == '>' && buffer[1] != '>')
		return (TOKEN_REDIRECT_OUT);
	else if (buffer[0] == '>' && buffer[1] == '>')
		return (TOKEN_REDIRECT_APPEND);
	else
		return (TOKEN_WORD);
}

t_token	*lexical_push_back(t_token *token, char *buffer)
{
	t_token	*tmp;
	t_token	*current;

	current = token;
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->token_type = check_token_type(buffer);
	tmp->file_name = ft_strdup(buffer);
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!token)
	{
		token = tmp;
		return (token);
	}
	else
	{
		while (current->next)
			current = current->next;
	}
	current->next = tmp;
	tmp->prev = current;
	return (token);
}

int is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';' || c == '(' || c == ')' || c == '&');
}

char* add_spaces_around_specials(const char* buffer)
{
	size_t i = 0, j = 0;
	size_t len = ft_strlen(buffer);
	char* result = malloc(len * 3 + 1);

	if (!result)
		return NULL;
	while (buffer[i])
	{
		if (is_special(buffer[i]))
		{
            if ((buffer[i] == '<' && buffer[i + 1] == '<') ||
			(buffer[i] == '>' && buffer[i + 1] == '>') ||
			(buffer[i] == '|' && buffer[i + 1] == '|') ||
			(buffer[i] == '&' && buffer[i + 1] == '&'))
            {
                if (j > 0 && result[j - 1] != ' ')
                    result[j++] = ' ';
                result[j++] = buffer[i];
                result[j++] = buffer[i + 1];
                i += 2;
                if (buffer[i] && buffer[i] != ' ')
                    result[j++] = ' ';
                continue;
            }
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			result[j++] = buffer[i];
			if (buffer[i + 1] && buffer[i + 1] != ' ')
				result[j++] = ' ';
		}
		else
			result[j++] = buffer[i];
		i++;
	}
	result[j] = '\0';
	return result;
}

t_token	*lexical(char *buf)
{
	t_token	*token;
	size_t	i;
	char	**buffer;
	char *buf_malloc;

	buf_malloc = add_spaces_around_specials(buf);
	i = 0;
	token = NULL;
	buffer = ft_split(buf_malloc, ' ');
	while (buffer[i])
		token = lexical_push_back(token, buffer[i++]);
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(token))
		return (token);
	return (token);
}
// 	// insert_sort_for_list(token);
// 	// while (token) 
// 	// {
// 	//     printf("%s->", token->file_name);
// 	//     token = token->next;
// 	// }
// 	// printf("\n");