/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/27 12:52:10 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	validate_and_count(t_token *temp, t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = temp;
	while (tmp != token)
	{
		if (tmp->token_type == TOKEN_WORD)
			count++;
		else if (!tmp->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else if (tmp->next->token_type != TOKEN_WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tmp->next->cmd);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (count);
}

static char	**init_argv(t_redirect **redirect, t_token *token, t_token *temp)
{
	char	**argv;
	int		count;

	count = validate_and_count(temp, token);
	if (count < 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	fill_argv_and_redirects(redirect, argv, temp, token);
	return (argv);
}

static int	push_back_command(t_command **command,
	t_token *token, t_token *temp)
{
	t_command	*new_node;
	t_command	*cur;

	new_node = (t_command *)malloc(sizeof(t_command));
	new_node->redirect = NULL;
	new_node->argv = init_argv(&new_node->redirect, temp, token);
	if (!(new_node->argv))
	{
		free(new_node);
		return (-1);
	}
	new_node->next = NULL;
	if (!*command)
		*command = new_node;
	else
	{
		cur = *command;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
	return (0);
}

int	parsing(t_command **command, t_token *token)
{
	t_token	*start;
	t_token	*tmp;

	start = token;
	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_PIPE)
		{
			if (push_back_command(command, start, tmp) == -1)
			{
				printf("-21\n");
				return (-1);
			}
			start = tmp->next;
		}
		tmp = tmp->next;
	}
	if (start)
	{
		push_back_command(command, start, NULL);
	}
	return (0);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_list = NULL;
	shell->token = NULL;
	shell->buffer = NULL;
	shell->env = env;
	init_env(&shell->env_list, shell->env);
	return (shell);
}
