/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/04 17:29:26 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

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
	tmp->cmd = ft_strdup(buffer);
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

// int find_open_34(char* str, char elem)
// {
// 	size_t i = 0;
// 	while (str + )
// }

// int find_close_34(char* str, char elem)
// {
// 	size_t i = 0;
// 	while ()
// }

char* find_bracket(char* buffer)
{
	size_t i = 0;
	size_t j = 0;
	size_t open = 0;
	size_t close = 0;
	char* str = NULL;
	char* line = NULL;
	printf("' = %c\n", 39);
	while (buffer[i])
	{
		if (buffer[i] == 39 || buffer[i] == 34)
		{
			j = i;
			open = ++i;
			close = i;
			close++;
			
			if (buffer[j] && buffer[j] == 39)
			{
				printf("open = %zu\n", open);
				while (buffer[close])
				{
					printf("buffer[%zu] = %c\n", i, buffer[i]);
					if (buffer[close] == 39)
					{
						break;
					}
					close++;
				}
				printf("close = %zu\n", close);
				if ((close - open) > 1)
				{
					str = (char*)malloc(sizeof(char) * (close - open + 1));
					if (!str)
					{
						printf("str malloc ' ' faild\n");
						exit (0);
					}
					j = 0;
					while (buffer[open + j] && (open + j) < close)
					{
						str[j] = buffer[open + j];
						++j;
					}
					str[j] = '\0';
					line = ft_strjoin(line, str);
					free(str);
					str = NULL;
					i = close;
				}
				
			}
			else if (buffer[j] == 34)
			{	
				if (buffer[j] && buffer[j] == 34)
				{
					printf("open = %zu\n", open);
					while (buffer[close])
					{
						printf("buffer[%zu] = %c\n", i, buffer[i]);
						if (buffer[close] == '"')
						{
							break;
						}
						close++;
					}
					printf("close = %zu\n", close);
					if ((close - open) > 1)
					{
						str = (char*)malloc(sizeof(char) * (close - open + 1));
						if (!str)
						{
							printf("str malloc ' ' faild\n");
							exit (0);
						}
						j = 0;
						while (buffer[open + j] && (open + j) < close)
						{
							str[j] = buffer[open + j];
							++j;
						}
						str[j] = '\0';
						line = ft_strjoin(line, str);
						free(str);
						str = NULL;
						i = close;
					}
				}
			}
		}
		++i;
	}
	printf("line = %s\n", line);

	return line;	
}

t_token	*lexical(t_shell *shell)
{
	size_t	i;
	char	**buffer;
	char	*buf_malloc;
	printf("shell->buffer = %s\n", shell->buffer);
	if (!find_bracket(shell->buffer))
	{
		return NULL;
	}
	buf_malloc = add_spaces_around_specials(shell->buffer);
	i = 0;
	shell->token = NULL;
	buffer = ft_split(buf_malloc, ' ');
	while (buffer[i])
		shell->token = lexical_push_back(shell->token, buffer[i++]);
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(shell->token))
		return (NULL);
	return (shell->token);
}
