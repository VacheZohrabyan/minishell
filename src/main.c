/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 15:08:53 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	
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
			if (parsing(&(shell->command) ,shell->token) == -1)
			{
				token_node_free(&shell->token);
				free_command(shell->command);
				continue;
			}
			gnacinq(shell->command);
			run(shell);
			token_node_free(&shell->token);
			free_command(shell->command);
		}
		free(shell->buffer);
		shell->buffer = NULL;
	}
	free_command(shell->command);
	printf("stex\n");
	token_node_free(&shell->token);
	free_env(shell->env_list);
	free(shell);
	// free(shell);
	return (0);
}
