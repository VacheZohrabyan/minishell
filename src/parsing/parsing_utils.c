/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:50:54 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 14:39:00 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static t_redirect	*init_new_redirect(t_token *tmp)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	new_redirect->token_type = tmp->token_type;
	tmp = tmp->next;
	new_redirect->file_name = ft_strdup(tmp->cmd);
	new_redirect->next = NULL;
	return (new_redirect);
}

static void	add_redirect(t_redirect **redirect, t_token *tmp)
{
	t_redirect	*new_redirect;
	t_redirect	*cur;

	new_redirect = init_new_redirect(tmp);
	if (!*redirect)
		*redirect = new_redirect;
	else
	{
		cur = *redirect;
		while (cur->next)
			cur = cur->next;
		cur->next = new_redirect;
	}
}

static int	add_word(char **argv, int i, t_token *tmp)
{
	argv[i] = ft_strdup(tmp->cmd);
	return (i + 1);
}

void	fill_argv_and_redirects(t_redirect **redirect,
	char **argv, t_token *temp, t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = temp;
	while (tmp != token)
	{
		if (tmp->token_type == TOKEN_WORD)
			i = add_word(argv, i, tmp);
		else
			add_redirect(redirect, tmp);
		tmp = tmp->next;
	}
	argv[i] = NULL;
}
