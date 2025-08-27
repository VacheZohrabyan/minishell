/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/27 10:49:31 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void push_back_redirect(t_redirect** redirect, t_token* token, t_token* temp)
{
	t_redirect* new_redirect;
	t_redirect* current = *redirect;
	t_token* tmp = temp;
	while (tmp != token)
	{
		if (tmp->token_type != TOKEN_WORD)
		{
			new_redirect = (t_redirect*)malloc(sizeof(t_redirect));
			new_redirect->token_type = tmp->token_type;
			tmp = tmp->next;
			new_redirect->file_name = ft_strdup(tmp->cmd);
			new_redirect = NULL;
			if (!*redirect && tmp->token_type != TOKEN_WORD)
				*redirect = new_redirect;
			else
			{
				while (current->next)
					current = current->next;
				current = new_redirect;
			}
		}
		tmp = tmp->next;
	}
}

char** init_argv(t_redirect** redirect, t_token* token, t_token* temp)
{
	int count = 0;
	t_token *tmp = temp;
    while (tmp != token) {
        if (tmp->token_type == TOKEN_WORD)
            count++;
		else if (tmp && tmp->next->token_type != TOKEN_WORD && !count)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			exit(0);
		}
		else if (tmp && tmp->next->token_type != TOKEN_WORD && count)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->cmd);
			exit(0);
		}
		
        tmp = tmp->next;
    }
    char **argv = malloc(sizeof(char*) * (count + 1));
    int i = 0;
    tmp = temp;
    while (tmp != token) {
        if (tmp->token_type == TOKEN_WORD)
            argv[i++] = ft_strdup(tmp->cmd);
        else {
            t_redirect *node = malloc(sizeof(t_redirect));
            node->token_type = tmp->token_type;
            tmp = tmp->next;
            node->file_name = ft_strdup(tmp->cmd);
            node->next = NULL;
            if (!*redirect)
                *redirect = node;
            else {
                t_redirect *cur = *redirect;
                while (cur->next)
                    cur = cur->next;
                cur->next = node;
            }
        }
        tmp = tmp->next;
    }
    argv[i] = NULL;
    return argv;
}


void push_back_command(t_command** command, t_token* token, t_token* temp)
{
	 t_command *node = malloc(sizeof(t_command));
    node->redirect = NULL;
    node->argv = init_argv(&node->redirect, temp, token);
    node->next = NULL;
    if (!*command)
        *command = node;
    else {
        t_command *cur = *command;
        while (cur->next)
            cur = cur->next;
        cur->next = node;
    }
}

void parsing(t_command** command, t_token* token)
{
	 t_token *start = token;
    t_token *tmp = token;
    while (tmp) {
        if (tmp->token_type == TOKEN_PIPE) {
            push_back_command(command, start, tmp);
            start = tmp->next;
        }
        tmp = tmp->next;
    }
    if (start)
        push_back_command(command, start, NULL);
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
