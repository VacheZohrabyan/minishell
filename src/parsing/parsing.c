/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/13 17:31:22 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static t_redirect	*init_new_redirect(t_token **tmp)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	new_redirect->token_type = (*tmp)->token_type;
	(*tmp) = (*tmp)->next;
	if ((*tmp)->cmd == NULL)
	{
		free(new_redirect);
		return (printf("minishell: syntax error near unexpected token `newline'\n"), NULL);
	}
	new_redirect->file_name = ft_strdup((*tmp)->cmd);
	new_redirect->next = NULL;
	return (new_redirect);
}

static int	add_redirect(t_redirect **redirect, t_token **tmp)
{
	t_redirect	*new_redirect;
	t_redirect	*cur;

	new_redirect = init_new_redirect(tmp);
	if (new_redirect == NULL)
		return -1;
	if (!*redirect)
		*redirect = new_redirect;
	else
	{
		cur = *redirect;
		while (cur->next)
			cur = cur->next;
		cur->next = new_redirect;
	}
	return 0;
}

static int	add_word(char **argv, int i, t_token *tmp)
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
	if (tmp->token_type == TOKEN_WORD)
	{
		tmp = tmp->next;
		++count;
	}
	while (tmp != end)
	{
		if (tmp->token_type != TOKEN_WORD && tmp->next->token_type == TOKEN_WORD)
		{
			tmp = tmp->next;
			continue;
		}
		else if (tmp->token_type == TOKEN_WORD && tmp->prev->token_type == TOKEN_WORD)
			++count;
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	return (count);
}

int	fill_argv_and_redirects(t_redirect **redirect, char **argv,
		t_token *start, t_token *end)
{
	t_token	*tmp;
	int		i;
	int		count = 0;

	count = validate_and_count(start, end);
	i = 0;
	tmp = start;
	if (tmp->token_type == TOKEN_WORD)
	{
		i = add_word(argv, i, tmp);
		--count;
		tmp = tmp->next;
	}
	while (tmp && tmp != end)
	{
		if (tmp->token_type != TOKEN_WORD && tmp->next->token_type == TOKEN_WORD)
		{
			if (add_redirect(redirect, &tmp))
				return -1;
		}
		if (tmp->prev && tmp->token_type == TOKEN_WORD && tmp->prev->token_type == TOKEN_WORD && count)
		{
			i = add_word(argv, i, tmp);
			--count;
		}
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	if (argv)
		argv[i] = NULL;
	return 0;
}

static char	**init_argv(t_redirect **redirect, t_token *end, t_token *start, int *flag)
{
	char	**argv;
	int		count;

	count = validate_and_count(start, end);
	argv = NULL;
	if (count > 0)
	{
		argv = (char **)malloc(sizeof(char *) * (count + 1));
		if (!argv)
		return (NULL);
	}
	if (fill_argv_and_redirects(redirect, argv, start, end) == -1)
		return (*flag = -1, NULL);
	return (argv);
}

static int	push_back_command(t_command **command, t_token *start, t_token *end)
{
	t_command	*new_node;
	t_command	*cur;
	int flag = 0;
	
	new_node = (t_command *)malloc(sizeof(t_command));
	new_node->redirect = NULL;
	new_node->argv = init_argv(&new_node->redirect, end, start, &flag);
	if (flag == -1)
	{
		free_command(command);
		command = NULL;
		return -1;
	}
	new_node->next = NULL;
	if (!(*command))
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
	*command = NULL;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_PIPE)
		{
			if (push_back_command(command, start, tmp) == -1)
			{
				free_command(command);
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
	shell->command = NULL;
	shell->history_fd = -1;
	init_env(&(shell->env_list), shell->env);
	init_env(&(shell->export_list), shell->env);
	shell->history = ft_strjoin(get_env_param(shell->env_list, "HOME", 1),
			"/.minishell_history");
	return (shell);
}
