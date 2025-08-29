/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/29 17:34:43 by zaleksan         ###   ########.fr       */
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
			if (parsing(&(shell->command) ,shell->token) == -1)
			{
				token_node_free(&shell->token);
				free_command(&(shell->command));
				continue;
			}
			// int i = 0;
			// while (shell->command)
			// {
			// 	i = 0;
			// 	while (shell->command->argv[i] && shell->command->argv)
			// 	{
            // 		printf("  argv[%d] = %s\n", i, shell->command->argv[i]);
			// 		++i;
			// 	}
			// 	while (shell->command->redirect)
			// 	{
			// 		printf("  redirect: type=%d, file=%s\n", shell->command->redirect->token_type, shell->command->redirect->file_name);
			// 		shell->command->redirect = shell->command->redirect->next;
			// 	}
			// 	shell->command = shell->command->next;
			// }
			gnacinq(shell);
			run(shell);
			// token_node_free(&shell->token);
			free_command(&(shell->command));
		}
		free(shell->buffer);
		shell->buffer = NULL;
	}
	free_command(&(shell->command));
	printf("stex\n");
	token_node_free(&shell->token);
	free_env(shell->env_list);
	free(shell);
	// free(shell);
	return (0);
}
