/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/28 15:08:53 by zaleksan         ###   ########.fr       */
=======
/*   Updated: 2025/08/28 14:31:13 by vzohraby         ###   ########.fr       */
>>>>>>> 44af7940553ff4dcaeed2cd9cda7b58c49888632
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
<<<<<<< HEAD
				free_command(shell->command);
=======
				free_command(&command);
>>>>>>> 44af7940553ff4dcaeed2cd9cda7b58c49888632
				continue;
			}
			gnacinq(shell->command);
			run(shell);
			token_node_free(&shell->token);
<<<<<<< HEAD
			free_command(shell->command);
=======
			free_command(&command);
			printf("command main = %p\n", command);
>>>>>>> 44af7940553ff4dcaeed2cd9cda7b58c49888632
		}
		free(shell->buffer);
		shell->buffer = NULL;
	}
<<<<<<< HEAD
	free_command(shell->command);
=======
	free_command(&command);
	// printf("command main = %p\n", command);
>>>>>>> 44af7940553ff4dcaeed2cd9cda7b58c49888632
	printf("stex\n");
	token_node_free(&shell->token);
	free_env(shell->env_list);
	free(shell);
	// free(shell);
	return (0);
}
