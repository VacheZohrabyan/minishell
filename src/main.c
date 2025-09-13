/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/13 11:53:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

void shlvl(t_shell* shell)
{
	t_env_node* env = shell->env_list->buffer_env[0];
	
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			free(env->value);
			env->value = ft_strdup("1");
			return;
		}
		env = env->next;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	shell = NULL;
	if (argc != 1 || !argv[0])
		return (0);
	shell = init_shell(env);
	init_shell_history(shell);
	load_history(shell);
	shlvl(shell);
	sig();
	while (1)
	{
		shell->buffer = readline("minishell> ");
		if (!shell->buffer)
		{
			printf("exit\n");
			break ;
		}
		else if (shell->buffer[0] == '\0')
			continue;
		record_history(shell, shell->buffer);
		shell->token = lexical(shell);
		if (shell->token)
		{
			if (parsing(&(shell->command), shell->token) == -1)
			{
				token_node_free(&shell->token);
				free_command(&(shell->command));
				break ;
			}
			run(shell);

			token_node_free(&shell->token);
			free_command(&(shell->command));
		}
		free(shell->buffer);
		shell->buffer = NULL;
	}
	close_shell_history(shell);
	free_command(&(shell->command));
	token_node_free(&shell->token);
	free_env(shell->env_list);
	free(shell->history);
	free(shell);
	return (0);
}
