/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/26 15:41:43 by vzohraby         ###   ########.fr       */
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
			command = parsing(shell->token);
			if (!command)
			{
				printf("chexav\n");
			}
			int i = 0;
			while (command)
			{
				if (command->token)
				{
					printf("%s ", command->reidrect->argv);
					command = command->next;
					continue;
				}
				while (command->argv[i])
				{
					printf("%s ", command->argv[i]);
					++i;
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
	// free(shell);
	return (0);
}
