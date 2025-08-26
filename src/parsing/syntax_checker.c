/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:44 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/26 14:10:45 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	valid_syntax_breket(t_token *current)
{
	t_token	*tmp;
	int		open;
	int		close;
	int		flag_open;
	int		flag_close;

	tmp = current;
	flag_close = 0;
	flag_open = 0;
	open = 0;
	close = 0;
	if (!current)
		return (0);
	while (tmp)
	{
		chlp1(tmp, &open, &flag_open);
		chlp2(tmp, &close, &flag_close, &open);
		tmp = tmp->next;
	}
	if (!check(open, close, flag_open, flag_close))
		return (0);
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
					" near unexpected token `%s'\n", str), 0);
		tmp = tmp->next;
	}
	if (tmp && tmp->token_type == token_type)
		return (printf("bash: syntax error"
				" near unexpected token `%s'\n", str), 0);
	return (1);
}

int	valid_syntax_pipe_or_and(t_token *token)
{
	t_token	*tmp;
	tmp = token;
	if (tmp->token_type != TOKEN_WORD)
		if ((tmp->token_type == TOKEN_PIPE) || (tmp->token_type == TOKEN_OR) || (tmp->token_type == TOKEN_AND))
			return (printf("bash: syntax error"
					" near unexpected token `%s'\n", tmp->cmd), 0);
	// if (tmp->token_type != TOKEN_WORD)
	// 	if (tmp->token_type == TOKEN_OR)
	// 		return (printf("bash: syntax error"
	// 				" near unexpected token `||'\n"), 0);
	// if (tmp->token_type != TOKEN_WORD)
	// 	if (tmp->token_type == TOKEN_AND)
	// 		return (printf("bash: syntax error"
	// 				" near unexpected token `&&'\n"), 0);
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
	if (!valid_syntax_breket(token) || !valid_syntax_pipe_or_and(token))
	{
		token_node_free(&token);
		return (0);
	}
	return (1);
}
