/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:48:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 18:25:46 by vzohraby         ###   ########.fr       */
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

t_token	*lexical_push_back(t_shell *shell, char *buffer)
{
	t_token	*tmp;
	t_token	*current;

	current = shell->token;
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->token_type = check_token_type(buffer);
	tmp->cmd = ft_strdup(buffer);
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
	buffer = my_split(buf_malloc, shell->env_list->env_head,
			' ', &(shell->status));
	while (buffer[i])
		shell->token = lexical_push_back(shell, buffer[i++]);
	split_free(&buffer);
	free(buf_malloc);
	if (!syntax_checker(shell->token))
		return (NULL);
	return (shell->token);
}

char	*expend_env_function2(char *str, char *out, int *i)
{
	char	*tmp;

	tmp = ft_strdup("$?");
	if (ft_strlen(str) == 2)
	{
		out = ft_strdup(tmp);
		free(tmp);
		(*i) += 2;
		return (out);
	}
	free(tmp);
	tmp = ft_itoa(g_exit_status);
	out = ft_strjoin(out, tmp);
	free(tmp);
	(*i) = (*i) + 2;
	return (out);
}
