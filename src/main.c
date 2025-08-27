/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/27 12:13:56 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	t_command* command = NULL;
	shell = NULL;
	if (argc != 1 || !argv[0])
		return (0);
	shell = init_shell(env);
	sig();
	while (1)
	{
		shell->buffer = readline("minishell>"); // PROMPT
		if (!shell->buffer)
		{
			printf("exit\n");
			break ;
		}
		add_history(shell->buffer);
		shell->token = lexical(shell);
		if (shell->token)
		{
			printf("stex\n");
			if (parsing(&command ,shell->token) == -1)
			{
				continue;
			}
			if (!command)
			{
				continue;
			}
			int i = 0;
			while (command)
			{
				i = 0;
				while (command->argv[i] && command->argv)
				{
            		printf("  argv[%d] = %s\n", i, command->argv[i]);
					++i;
				}
				while (command->redirect)
				{
					printf("  redirect: type=%d, file=%s\n", command->redirect->token_type, command->redirect->file_name);
					command->redirect = command->redirect->next;
				}
				command = command->next;
			}
			token_node_free(&shell->token);
		}
		free(shell->buffer);
		shell->buffer = NULL;
	}
	token_node_free(&shell->token);
	free_env(shell->env_list);
	free(shell);
	// free(shell);
	return (0);
}
