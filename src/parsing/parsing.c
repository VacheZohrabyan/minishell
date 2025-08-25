/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/25 23:13:52 by vzohraby         ###   ########.fr       */
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
	
	if (*command)
	{
		while (current->next)
			current = current->next;
	}
	if (tmp->token_type == TOKEN_WORD)
	{
		new_command->argv = (char**)malloc(sizeof(char*) * (word_count(tmp) + 1));
		if (!(new_command->argv))
			exit (0); //stex hendl kanes
		new_command->reidrect = NULL;
		new_command->herodoc = 0;
		printf("stex\n");
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
			current->next = NULL;
			current->reidrect = NULL;
			new_command->argv[i] = NULL;
		}
	}
	else
	{
		new_command->argv = NULL;
		if (tmp->token_type == TOKEN_HEREDOC)
		{
			new_command->herodoc = 1;
			new_command->reidrect = (t_reidrect*)malloc(sizeof(t_reidrect));
			if ((new_command->reidrect->fd = open(tmp->next->cmd, O_RDONLY | O_WRONLY | O_CREAT)) < 0)
			{
				exit(0); //esel hendl kanes
			}
			new_command->reidrect->argv = ft_strdup(tmp->cmd);
			if (!(new_command->reidrect->argv))
			{
				exit(0); //esel hendl kanes
			}
		}
		else
		{
			new_command->reidrect = (t_reidrect*)malloc(sizeof(t_reidrect));
			new_command->reidrect->argv = ft_strdup(tmp->cmd);
			new_command->herodoc = 0;
			new_command->reidrect->argv = ft_strdup(tmp->cmd);
			if (!(new_command->reidrect->argv))
			{
				exit(0); //esel hendl kanes
			}
		}
		*token = tmp;
	}
}

t_command* parsing(t_token* token)
{
	t_token* tmp = token;
	t_command* command = NULL;
	printf("parsing\n");
	while (tmp)
	{
		push_back_command(&command, &tmp);
		if (!tmp)
			return command;
		tmp = tmp->next;
	}
	return command;
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
