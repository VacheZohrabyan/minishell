/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 14:25:01 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int heredoc_file_open_wr(t_redirect *redirect)
{
	int fd = 0;
	char* buffer;
	fd = open(redirect->file_name, O_RDWR | O_CREAT, 0777);
	if (fd != -1)
	{
		while (1)
		{
			buffer = readline(">");
			if (!buffer)
			{
				printf("minishell: warning: here-document at line 75 delimited by end-of-file (wanted `ld')\n");
				return (-1);
			}
			write(fd, buffer, ft_strlen(buffer));
			write(fd, "\n", 1);
			if (!ft_strncmp(redirect->file_name, buffer, ft_strlen(buffer)))
				break;
		}
	}
	while ((buffer = get_next_line(fd)))
	{
		printf("%s\n", buffer); //history.file
		free(buffer);
		buffer = NULL;
	}
	close(fd);
	return (0);
}

int any(t_redirect* redirect)
{
	t_redirect* tmp = redirect;

	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)
		{
			printf("stexic\n");
			if (access(tmp->file_name, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory\n", tmp->file_name);
				return -1;
			}
			printf("kamel stexic\n");
		}
		else if (tmp->token_type == TOKEN_HEREDOC)
		{
			if (heredoc_file_open_wr(tmp) == -1)
				return (-1);
		}
		else 
		{
			
		}
		tmp = tmp->next;
	}
	return 0;
}

int gnacinq(t_command* command)
{
	t_command *tmp = command;
	
	while (tmp)
	{
		if (tmp->redirect != NULL)
		{
			if (any(tmp->redirect) != -1)
				return -1;
		}
		tmp = tmp->next;
	}
	return 0;
}