/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 17:45:55 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

t_redirect	*init_new_redirect(t_token **tmp)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	new_redirect->token_type = (*tmp)->token_type;
	(*tmp) = (*tmp)->next;
	if ((*tmp)->cmd == NULL)
	{
		free(new_redirect);
		return (printf("minishell: syntax error "
				"near unexpected token `newline'\n"), NULL);
	}
	new_redirect->file_name = ft_strdup((*tmp)->cmd);
	new_redirect->next = NULL;
	return (new_redirect);
}

int	add_redirect(t_redirect **redirect, t_token **tmp)
{
	t_redirect	*new_redirect;
	t_redirect	*cur;

	new_redirect = init_new_redirect(tmp);
	if (new_redirect == NULL)
		return (-1);
	if (!*redirect)
		*redirect = new_redirect;
	else
	{
		cur = *redirect;
		while (cur->next)
			cur = cur->next;
		cur->next = new_redirect;
	}
	return (0);
}

int	add_word(char **argv, int i, t_token *tmp)
{
	argv[i] = ft_strdup(tmp->cmd);
	return (i + 1);
}

int	validate_and_count(t_token *start, t_token *end)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = start;
	if (tmp->token_type == TOKEN_WORD && ++count)
		tmp = tmp->next;
	while (tmp != end)
	{
		if (tmp->token_type != TOKEN_WORD
			&& tmp->next->token_type == TOKEN_WORD)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->token_type == TOKEN_WORD
			&& tmp->prev->token_type == TOKEN_WORD)
			++count;
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	return (count);
}
