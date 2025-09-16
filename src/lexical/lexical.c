/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 11:28:52 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

t_token_type	check_token_type(char *buffer)
{
	if (buffer[0] == '|' && buffer[1] != '|')
		return (TOKEN_PIPE);
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

char	*check_prompt(t_shell *shell, char *buffer)
{
	t_env_node	*tmp;

	tmp = shell->env_list->env_head;
	if (buffer[0] == '$' && (buffer[1] == '"' || buffer[1] == '\''))
		return (ft_strdup(buffer + 1));
	else if (buffer[0] == '$' && buffer[1] != '\0')
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, buffer + 1) == 0)
				return (ft_strdup(tmp->value));
			tmp = tmp->next;
		}
	}
	else if (buffer[0] == '\'' && buffer[0] != '\0')
		return (ft_strdup(buffer));
	return (ft_strdup(buffer));
}

t_token	*lexical_push_back(t_shell *shell, char *buffer)
{
	t_token	*tmp;
	t_token	*current;

	current = shell->token;
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->token_type = check_token_type(buffer);
	tmp->cmd = check_prompt(shell, buffer);
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!shell->token)
	{
		shell->token = tmp;
		return (shell->token);
	}
	else
	{
		while (current->next)
			current = current->next;
	}
	current->next = tmp;
	tmp->prev = current;
	return (shell->token);
}

t_token	*lexical(t_shell *shell)
{
	size_t	i;
	char	**buffer;
	char	*buf_malloc;

	buf_malloc = add_spaces_around_specials(shell->buffer);
	i = 0;
	shell->token = NULL;
	buffer = my_split(buf_malloc, shell->env_list->env_head, ' ');
	while (buffer[i])
		shell->token = lexical_push_back(shell, buffer[i++]);
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(shell->token))
		return (NULL);
	return (shell->token);
}
