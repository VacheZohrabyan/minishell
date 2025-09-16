/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 20:05:54 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	**init_argv(t_redirect **redirect, t_token *end, t_token *start,
		int *flag)
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

int	push_back_command(t_command **command, t_token *start, t_token *end)
{
	t_command	*new_node;
	t_command	*cur;
	int			flag;

	flag = 0;
	new_node = (t_command *)malloc(sizeof(t_command));
	new_node->redirect = NULL;
	new_node->argv = init_argv(&new_node->redirect, end, start, &flag);
	if (flag == -1)
	{
		free_command(command);
		command = NULL;
		return (-1);
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
				g_exit_status = 1;
				return (-1);
			}
			start = tmp->next;
		}
		tmp = tmp->next;
	}
	if (start && push_back_command(command, start, NULL) == -1)
	{
		g_exit_status = 1;
		return (-1);
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
