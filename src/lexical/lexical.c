/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/23 14:56:57 by zaleksan         ###   ########.fr       */
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
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(shell->token))
		return (NULL);
	return (shell->token);
}
