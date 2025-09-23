/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:39:55 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/23 18:45:33 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	any_utils_in(t_redirect *tmp)
{
	if (tmp->token_type == TOKEN_REDIRECT_IN)
	{
		tmp->fd = open(tmp->file_name, O_RDONLY);
		if (tmp->fd == -1)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			perror(tmp->file_name);
			g_exit_status = 1;
			return (-1);
		}
		tmp->to = STDIN_FILENO;
	}
	return (0);
}

static int	any_utils_out(t_redirect *tmp)
{
	if (tmp->token_type == TOKEN_REDIRECT_OUT)
	{
		tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (tmp->fd == -1)
		{
			if (access(tmp->file_name, W_OK) == -1)
				write(STDERR_FILENO, "minishell: Permission denied\n", 29);
			else
			{
				write(STDOUT_FILENO, "minishell: ", 11);
				perror(tmp->file_name);
			}
			g_exit_status = 1;
			return (-1);
		}
		tmp->to = STDOUT_FILENO;
	}
	return (0);
}

static int	any_utils_append(t_redirect *tmp)
{
	if (tmp->token_type == TOKEN_REDIRECT_APPEND)
	{
		tmp->fd = open(tmp->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->fd == -1)
		{
			if (access(tmp->file_name, W_OK) == -1)
				write(STDERR_FILENO, "minishell: Permission denied\n", 29);
			else
			{
				write(STDOUT_FILENO, "minishell: ", 11);
				perror(tmp->file_name);
			}
			g_exit_status = 1;
			return (-1);
		}
		tmp->to = STDOUT_FILENO;
	}
	return (0);
}

int	any(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)
		{
			if (any_utils_in(tmp) == -1)
				return (-1);
		}
		else if (tmp->token_type == TOKEN_REDIRECT_OUT)
		{
			if (any_utils_out(tmp) == -1)
				return (-1);
		}
		else if (tmp->token_type == TOKEN_REDIRECT_APPEND)
		{
			if (any_utils_append(tmp) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
