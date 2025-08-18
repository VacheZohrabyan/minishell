/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:11:25 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/18 22:18:21 by vzohraby         ###   ########.fr       */
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
	return (ft_strcmp(str, "echo") == 0 
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit")) == 0;
}

int	command_token(char *str)
{
	return (ft_strcmp(str, "(") == 0
	 	|| ft_strcmp(str, ")") == 0
		|| ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "||") == 0
		|| ft_strcmp(str, "&&") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0);
}

char** join_meny_path(t_token** token) // esem avelacre
{
    size_t size_word = 0;
	t_token *tmp = *token;
    while (tmp && tmp->token_type == TOKEN_WORD) {
        size_word++;
        tmp = tmp->next;
    }
    char **argv = malloc(sizeof(char*) * (size_word + 1));
    if (!argv)
	{
        return NULL;
	}
	tmp = *token;
    for (size_t i = 0; i < size_word; i++) {
        argv[i] = ft_strdup(tmp->file_name);
        if (!argv[i]) {
            while (i > 0)
                free(argv[--i]);
            free(argv);
            return NULL;
        }
        tmp = tmp->next;
    }
    argv[size_word] = NULL;
	*token = tmp;
    return argv;
}

int command_word_for_os(t_token *token)
{
    t_token *tmp = token;
    char **argv = join_meny_path(&tmp); //es functian
    pid_t fork_pid = fork();

    if (fork_pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (fork_pid == 0)
    {
        execvp(argv[0], argv);
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
    return 0;
}

int	syntax(t_token *token)
{
	t_token *tmp = token;

    while (tmp)
    {
        if (tmp->token_type == TOKEN_WORD)
        {
            if (command_word(tmp->file_name))
            {
                printf("builtin: %s\n", tmp->file_name); //es printf khanes go biltinery kgres
            }
            else
            {
                command_word_for_os(tmp);
            }
        }
        else if (command_token(tmp->file_name))
        {
            printf("command_token\n"); //vaxy kanem
        }
        tmp = tmp->next;
    }
    return 1;
}
//u verj