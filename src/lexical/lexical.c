/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/08 18:14:47 by vzohraby         ###   ########.fr       */
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

char* check_bracket(char* buffer)
{
	size_t i = 0;
	size_t j = 0;
	size_t open = 0;
	size_t close = 0;
	char* str = NULL;
	char* line = NULL;
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
				while (buffer[close])
				{
					if (buffer[close] == 39)
					{
						break;
					}
					close++;
				}
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
					while (buffer[close])
					{
						if (buffer[close] == '"')
						{
							break;
						}
						close++;
					}
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
	free(buffer);
	return line;	
}

void funct(t_token* start, t_token* end)
{
	if (start == end)
	{
		
	}
	t_token* tmp = start;
	char* str = NULL;
	while (tmp != end->next)
	{
		str = ft_strjoin_gnl(str, tmp->cmd);
		str = ft_strjoin_gnl(str, " ");
		tmp = tmp->next;
	}
	str = check_bracket(str);
	t_token* new_node = (t_token*)malloc(sizeof(t_token));
	if (!new_node)
		return;
	new_node->cmd = str;
	new_node->token_type = TOKEN_WORD;
	new_node->prev = start->prev;
	new_node->next = end->next;
	if (start->prev)
		start->prev->next = new_node;
	if (end->next)
		end->next->prev = new_node;
	// while (start != end->next)
	// {
	// 	tmp = start;
	// 	start = start->next;
	// 	free(tmp->cmd);
	// 	tmp->cmd = NULL;
	// 	free(tmp);
	// 	tmp = NULL;
	// }
}

int find_bracket(char* str, int c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return 1;
		++i;
	}
	return 0;
}

int find_bracket_list(t_token** token)
{
	t_token* start = NULL;
	t_token* end = NULL;
	t_token* tmp = *token;
	while (tmp)
	{
		if ((find_bracket(tmp->cmd, 39) || find_bracket(tmp->cmd, 34)))
		{		
			start = tmp;
			break;
		}
		tmp = tmp->next;
	}
	if (!start)
	{
		printf("start is null\n");
		return 0;
	}
	tmp = start;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_WORD)
		{
			if ((find_bracket(tmp->cmd, 39) || find_bracket(tmp->cmd, 34)))
				end = tmp;
		}
		else if (tmp->token_type != TOKEN_WORD && end)
			break;
		tmp = tmp->next;
	}
	if (!end)
		return 0;
	funct(start, end);
	return 1;
}

void find_funct(t_token* token)
{
	t_token* tmp = token;
	while (tmp)
	{
		printf("stex\n");
		find_bracket_list(&tmp);
		tmp = tmp->next;
	}
}

t_token	*lexical(t_shell *shell)
{
	size_t	i;
	char	**buffer;
	char	*buf_malloc;
	buf_malloc = add_spaces_around_specials(shell->buffer);
	i = 0;
	shell->token = NULL;
	buffer = ft_split(buf_malloc, ' ');
	while (buffer[i])
		shell->token = lexical_push_back(shell->token, buffer[i++]);
	find_funct(shell->token);
	while (shell->token)
	{
		printf("%s", shell->token->cmd);
		shell->token = shell->token->next;
	}
	printf("\n");
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(shell->token))
		return (NULL);
	return (shell->token);
}
