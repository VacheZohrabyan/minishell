/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:11 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/30 15:46:00 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	check_double_operator(t_token *token, t_token_type token_type,
		const char *str)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == token_type)
		{
			if (!tmp->next)
			{
				write(STDERR_FILENO, "minishell: syntax error near unexpected "
					"token `", ft_strlen("minishell: syntax error "
						"near unexpected token `"));
				write(STDERR_FILENO, str, ft_strlen(str));
				write(STDERR_FILENO, "'\n", ft_strlen("'\n"));
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void	message_syntax_error(t_token *tmp, short flag)
{
	if (flag == 2)
	{
		write(STDERR_FILENO, "minishell: syntax error near "
			"unexpected token `|'\n", ft_strlen("minishell: syntax "
				"error near unexpected token `|'\n"));
	}
	else if (flag == 1)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected"
			" token `", ft_strlen("minishell: syntax "
				"error near unexpected token `"));
		write(STDERR_FILENO, tmp->cmd, ft_strlen(tmp->cmd));
		write(STDERR_FILENO, "'\n", ft_strlen("'\n"));
	}
	else if (flag == 0)
	{
		write(STDERR_FILENO, "minishell: syntax error "
			"near unexpected token `newline'\n", ft_strlen(""
				"minishell: syntax error near unexpected token "
				"`newline'\n"));
	}
}

int	urish_check_double_operator(t_token *token, t_token_type token_type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == token_type)
		{
			if (!tmp->next)
				return (message_syntax_error(tmp, 0), 0);
			if (tmp->next->token_type != TOKEN_WORD)
				return (message_syntax_error(tmp->next, 1), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	valid_syntax_pipe_or_and(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!tmp)
		return (0);
	if (tmp->token_type == TOKEN_PIPE)
		return (message_syntax_error(tmp, 2), 0);
	if ((tmp->token_type == TOKEN_REDIRECT_APPEND
			|| tmp->token_type == TOKEN_REDIRECT_IN
			|| tmp->token_type == TOKEN_REDIRECT_OUT
			|| tmp->token_type == TOKEN_HEREDOC)
		&& !tmp->next)
		return (message_syntax_error(tmp, 0), 0);
	if (!chlp1(token))
		return (0);
	return (1);
}

int	syntax_checker(t_token *token)
{
	if (!valid_syntax_pipe_or_and(token))
	{
		token_node_free(&token);
		g_exit_status = 2;
		return (0);
	}
	return (1);
}
