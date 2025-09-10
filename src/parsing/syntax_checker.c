/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:11 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/10 11:38:35 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	check_double_operator(t_token *token, t_token_type token_type,
		const char *str)
{
	t_token	*tmp = token;

	while (tmp)
	{
		if (tmp->token_type == token_type)
		{
			// case: operator is last
			if (!tmp->next)
				return (printf("minishell: syntax error near unexpected token `%s'\n", str), 0);
			// case: operator followed by another operator
			// if (tmp->next->token_type != TOKEN_WORD && tmp->next->token_type != TOKEN_LPAREN)
			// 	return (printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->cmd), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	urish_check_double_operator(t_token *token, t_token_type token_type)
{
	t_token *tmp = token;

	while (tmp)
	{
		if (tmp->token_type == token_type)
		{
			if (!tmp->next)
				return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
			if (tmp->next->token_type != TOKEN_WORD)
				return (printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->cmd), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	valid_syntax_pipe_or_and(t_token *token)
{
	t_token	*tmp = token;

	if (!tmp)
		return (0);

	// pipeline cannot start with pipe
	if (tmp->token_type == TOKEN_PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);

	// redirs cannot be last
	if ((tmp->token_type == TOKEN_REDIRECT_APPEND || tmp->token_type == TOKEN_REDIRECT_IN
		|| tmp->token_type == TOKEN_REDIRECT_OUT || tmp->token_type == TOKEN_HEREDOC)
		&& !tmp->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);

	if (!check_double_operator(token, TOKEN_PIPE, "|"))
		return (0);
	// if (!check_double_operator(token, TOKEN_OR, "||"))
	// 	return (0);
	// if (!check_double_operator(token, TOKEN_AND, "&&"))
	// 	return (0);

	if (!urish_check_double_operator(token, TOKEN_REDIRECT_APPEND))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_HEREDOC))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_REDIRECT_OUT))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_REDIRECT_IN))
		return (0);

	return (1);
}

int syntax_checker(t_token *token) 
{ 
	if (!valid_syntax_pipe_or_and(token)) 
	{ 
		token_node_free(&token); 
		return (0); 
	} 
	return (1); 
}