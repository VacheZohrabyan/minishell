/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:44 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/18 22:34:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	valid_syntax_breket(t_token *current)
{
	t_token	*tmp;
	int		count;

	tmp = current;
	count = 0;
	if (!current)
		return (0);
	while (tmp)
	{
		if (tmp->token_type == TOKEN_OPEN)
			++count;
		else if (tmp->token_type == TOKEN_CLOSE)
		{
			--count;
			if (count < 0)
				return (printf("syntax error"
						"near unexpected token `)'\n"), 0);
		}
		tmp = tmp->next;
	}
	if (count != 0)
		return (printf("syntax error"
				"near unexpected token `)'\n"), 0);
	return (1);
}

int	check_double_operator(t_token *token, t_token_type token_type,
		const char *str)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->next)
	{
		if (tmp->token_type == token_type && tmp->next->token_type)
			return (printf("bash: syntax error"
					"near unexpected token `%s'\n", str), 0);
		tmp = tmp->next;
	}
	if (tmp && tmp->token_type == token_type)
		return (printf("bash: syntax error"
				"near unexpected token `%s'\n", str), 0);
	return (1);
}

int	valid_syntax_pipe_or_and(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->token_type != TOKEN_WORD)
		if (tmp->token_type == TOKEN_PIPE)
			return (printf("bash: syntax error"
					"near unexpected token `|'\n"), 0);
	if (tmp->token_type != TOKEN_WORD)
		if (tmp->token_type == TOKEN_OR)
			return (printf("bash: syntax error"
					"near unexpected token `||'\n"), 0);
	if (tmp->token_type != TOKEN_WORD)
		if (tmp->token_type == TOKEN_AND)
			return (printf("bash: syntax error"
					"near unexpected token `&&'\n"), 0);
	if (!check_double_operator(token, TOKEN_PIPE, "|"))
		return (0);
	if (!check_double_operator(token, TOKEN_OR, "||"))
		return (0);
	if (!check_double_operator(token, TOKEN_AND, "&&"))
		return (0);
	return (1);
}

int	syntax_checker(t_token *token)
{
	if (!valid_syntax_breket(token))
	{
		token_node_free(&token);
		return (0);
	}
	if (!valid_syntax_pipe_or_and(token))
	{
		token_node_free(&token);
		return (0);
	}
	return (1);
}
