/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/25 18:37:03 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

size_t word_count(t_token* tmp)
{
	size_t size = 0;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_WORD)
		{
			++size;
			tmp = tmp->next;
			continue;
		}
		return size;
	}
	return size;
}


void push_back_command(t_command** command, t_token **token)
{
	t_command *current = *command;
	t_command *new_command = (t_command*)malloc(sizeof(t_command));
	t_token* tmp = *token;
	int i = 0;
	if (!new_command)
	{
		exit(0);
	}	
	
	if (!(*command))
	{
		new_command->argv = (char**)malloc(sizeof(char*) * word_count(tmp));
		if (!(new_command->argv))
			exit (0); //stex hendl kanes
		new_command->reidrect = NULL;
		new_command->herodoc = 0;
		if (tmp->token_type == TOKEN_WORD)
		{
			while (tmp)
			{
				if (tmp->token_type == TOKEN_WORD)
				{
					new_command->argv[i] = ft_strdup(tmp->cmd);
					++i;
					tmp = tmp->next;
					continue;
				}
				*token = tmp;
				current = new_command;
			}
		}
		else
		{
			t_reidrect* new_redir = new_command->reidrect = (t_reidrect*)malloc(sizeof(t_reidrect));
			new_redir->argv = ft_strdup(tmp->cmd);
			t_reidrect* current_redir = 
		}
	}
	else
	{
		
	}
}

t_command* parsing(t_token* token)
{
	t_token* tmp = token;
	t_command* command = NULL;
	command->reidrect = NULL;.
	+--
	while (tmp)
	{
		if (tmp->token_type == TOKEN_WORD)
		{
			push_back_command(&command, &tmp);
		}
	}
	return NULL;
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
