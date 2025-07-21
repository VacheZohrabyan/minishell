/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:04 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 17:51:32 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	is_valid_close_breaket(t_token *tmp, int open)
{
	if ((tmp->token_type == TOKEN_CLOSE && open == 0)
		|| (tmp->token_type == TOKEN_CLOSE
			&& tmp->prev->token_type == TOKEN_OPEN)
		|| (tmp->token_type == TOKEN_CLOSE
			&& tmp->prev->token_type == TOKEN_CLOSE)
		|| ((tmp->token_type == TOKEN_CLOSE)
			&& (tmp->prev != NULL && tmp->prev->token_type == TOKEN_WORD)))
	{
		return (0);
	}
	return (1);
}

int	check(int open, int close, int flag_open, int flag_close)
{
	if (open == 3 && open == close)
		return (printf("syntax error"
				" near unexpected token `)'\n"), 0);
	if (open != close)
		return (printf("syntax error"
				" near unexpected token `)'\n"), 0);
	if ((open == close) && (flag_close != flag_open))
		return (printf("syntax error"
				" near unexpected token `)'\n"), 0);
	return (1);
}

void	chlp1(t_token *tmp, int *open, int *flag_open)
{
	if (tmp->token_type == TOKEN_OPEN)
	{
		(*open) += 1;
		(*flag_open) = 1;
	}
}

void	chlp2(t_token *tmp, int *close, int *flag_close, int *open)
{
	if (!is_valid_close_breaket(tmp, *open))
	{
		(*close) += 1;
		(*flag_close) = 1;
	}
}
