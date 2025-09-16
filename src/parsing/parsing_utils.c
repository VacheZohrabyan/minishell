/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:48:36 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 17:51:35 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	handle_first_word(char **argv, int i, t_token **tmp, int *count)
{
	if (*tmp && (*tmp)->token_type == TOKEN_WORD)
	{
		i = add_word(argv, i, *tmp);
		--(*count);
		*tmp = (*tmp)->next;
	}
	return (i);
}

int	fill_argv_and_redirects(t_redirect **redirect, char **argv,
		t_token *start, t_token *end)
{
	t_token	*tmp;
	int		i;
	int		count;

	count = validate_and_count(start, end);
	i = 0;
	tmp = start;
	i = handle_first_word(argv, i, &tmp, &count);
	while (tmp && tmp != end)
	{
		if (tmp->token_type != TOKEN_WORD
			&& tmp->next->token_type == TOKEN_WORD)
			if (add_redirect(redirect, &tmp))
				return (-1);
		if (tmp->prev && tmp->token_type == TOKEN_WORD
			&& tmp->prev->token_type == TOKEN_WORD && count--)
			i = add_word(argv, i, tmp);
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	if (argv)
		argv[i] = NULL;
	return (0);
}
