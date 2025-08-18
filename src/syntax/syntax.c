/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:11:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/18 15:55:09 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		++i;
	}
	return (0);
}

int	command_word(char *str)
{
	return (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str,
			"pwd") || ft_strcmp(str, "export") || ft_strcmp(str, "unset")
		|| ft_strcmp(str, "env") || ft_strcmp(str, "exit"));
}

int	command_token(char *str)
{
	return (ft_strcmp(str, "(") || ft_strcmp(str, ")") || ft_strcmp(str, "|")
		|| ft_strcmp(str, "||") || ft_strcmp(str, "&&") || ft_strcmp(str, ">")
		|| ft_strcmp(str, ">>") || ft_strcmp(str, "<") || ft_strcmp(str, "<<"));
}

int	command_word_for_os(t_token *token)
{
	t_token	*tmp;
	char	*path;
	char	*full_path;
	pid_t	fork_pid;

	fork_pid = fork();
	if (fork_pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (fork_pid == 0)
	{
		path = "/bin/";
		tmp = token;
		full_path = ft_strjoin(path, tmp->file_name);
		if (!full_path)
		{
			perror("ft_strjoin failed");
			exit(EXIT_FAILURE);
		}
		char *argv[] = {tmp->file_name, NULL};
		if (execv(full_path, argv) == -1)
		{
			perror("command not found");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	return (0);
}

int	syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		printf("syntax\n");
	while (tmp)
	{
		if (!command_word(tmp->file_name) && tmp->token_type == TOKEN_WORD)
			return (printf("command_word\n"), 0);
		if (command_token(tmp->file_name) && tmp->token_type != TOKEN_WORD)
			return (printf("command_token\n"), 0);
		if (command_word_for_os(tmp) && tmp->token_type == TOKEN_WORD)
			return (printf("command_word_for_os\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}
