/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnacinq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:51:31 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 13:34:29 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void heredoc_file_open_wr(t_redirect *redirect)
{
	int fd = 0;
	int bytes;
	char buffer[BUFFER_SIZE];
	char* str;
	fd = open(redirect->file_name, O_RDWR | O_CREAT, 0777);
	if (fd != -1)
	{
		while ((bytes = read(0, buffer, BUFFER_SIZE)) != 0)
		{
			buffer[bytes] = '\0';
			write (fd, buffer, ft_strlen(buffer));
			if (ft_strncmp(redirect->file_name, buffer, ft_strlen(buffer) - 1) == 0)
				break;
			buffer[0] = '\0';
		}
	}
	while ((str = get_next_line(fd)))
	{
		add_history(str);
		free(str);
		str = NULL;
	}
	close(fd);
}

int any(t_redirect* redirect)
{
	t_redirect* tmp = redirect;

	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIRECT_IN)
		{
			if (access(tmp->file_name, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory", tmp->file_name);
				return -1;
			}
		}
		else if (tmp->token_type == TOKEN_HEREDOC)
		{
			heredoc_file_open_wr(tmp);
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