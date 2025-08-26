/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:56:33 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/26 19:18:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

// size_t word_count(t_token* tmp)
// {
// 	size_t size = 0;
// 	while (tmp)
// 	{
// 		if (tmp->token_type == TOKEN_WORD)
// 		{
// 			++size;
// 			tmp = tmp->next;
// 			continue;
// 		}
// 		return size;
// 	}
// 	return size;
// }

// int add_redirect_append(t_command** current, t_token** token)
// {
// 	while ((*token)->token_type == TOKEN_REDIRECT_APPEND)
// 	{
// 		(*token) = (*token)->next;
// 		if (!token)
// 		{
// 			printf("minishell: syntax error near unexpected token `newline'\n");
// 			//free() hendl;
// 			return -1;
// 		}
// 		else if ((*token)->token_type != TOKEN_WORD)
// 		{
// 			printf("minishell: syntax error near unexpected token %s\n", (*token)->cmd);
// 			//free() hendl;
// 			return -1;
// 		}
// 		(*current)->reidrect = (t_reidrect*)malloc(sizeof(t_reidrect));
// 		(*current)->reidrect->argv = ft_strdup((*token)->cmd);
// 		if (!((*current)->reidrect) || !((*current)->reidrect->argv))
// 		{
// 			printf("push_back_command (current->reidrect) malloc faild\n");
// 			exit(0);
// 		}
// 		if (access((*current)->reidrect->argv, F_OK) == -1)
// 		{
// 			while (access((*current)->reidrect->argv, R_OK | X_OK) == -1)
// 			{
// 				while (((*current)->reidrect->fd = open((*current)->reidrect->argv, O_WRONLY | O_CREAT, 0644)) < 0)
// 					;
// 			}
// 		}
// 		else if (access((*current)->reidrect->argv, R_OK | W_OK) < 0)
// 		{
// 			while (((*current)->reidrect->fd = open((*current)->reidrect->argv, O_WRONLY | O_CREAT, 0644)) < 0)
// 				;
// 		}
// 	}
// 	return 0;
// }


// int push_back_command(t_command** command, t_token **tmp)
// {
// 	t_command* current = *command;
// 	t_command* new_command = (t_command*)malloc(sizeof(t_command));
// 	t_token* token = *tmp;
// 	if (!new_command)
// 	{
// 		printf("push_back_command (new_command) malloc faild\n");
// 		exit(0);
// 	}
// 	if (current)
// 	{
// 		while (current)
// 			current = current->next;
// 	}
// 	else
// 	{
// 		*command = new_command;
// 		(*command)->next = NULL;
// 	}
// 	current = new_command;
// 	current->next = NULL;
// 	// if (token->token_type == TOKEN_REDIRECT_APPEND)
// 	// {
// 	// 	if (add_redirect_append(&current, &token))
// 	// 		return 1;
// 	// }
	
// 	return 0;
// }

// void parsing(t_token* token)
// {
// 	t_token* tmp = token;
// 	t_command* command = NULL;
// 	printf("parsing\n");
// 	while (tmp)
// 	{
// 		if (push_back_command(&command, &tmp) == -1)
// 			return NULL;
// 		if (!tmp)
// 			return command;
// 		tmp = tmp->next;
// 	}
// 	token = tmp;
// 	return command;
// }

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
	t_token* tmp = token;
	int size = 0;
	int i = 0;
	char** argv; 
	while (temp != token->next)
	{
		if (temp->token_type != TOKEN_WORD)
		{
			push_back_redirect(redirect, temp, token);
			temp = temp->next;
			if (temp->next != TOKEN_WORD)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				exit(0);
			}
			continue;
		}
		++size;
		temp = temp->next;
	}

	if (size == 0)
		return NULL;
	argv = (char**)malloc(sizeof(char*) * size);
	while (i < size)
	{
		argv[i] = ft_strdup(tmp->cmd);
		++i;
		tmp = tmp->next;
	}
	return argv;
}


void push_back_command(t_command** command, t_token* token, t_token* temp)
{
	t_command *new_command = (t_command*)malloc(sizeof(t_command));
	t_command *new_redirect = NULL;
	new_command->argv = init_argv(&new_redirect, temp, token);
	new_command->next = NULL;
	push_back_redirect(&(*command)->redirect, temp, token);
}

void parsing(t_command** command, t_token* token)
{
	t_token* tmp = token;
	t_token* temp = token;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_PIPE)
		{
			push_back_command(command, tmp, temp);
			temp = tmp;
		}
		tmp = tmp->next;
	}
	tmp = token;
	if(!(*command))
	{
		push_back_command(command, tmp, temp);
	}
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
