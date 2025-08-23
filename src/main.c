/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/23 18:05:39 by zaleksan         ###   ########.fr       */
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
			if (syntax(shell, shell->token))
			{
				printf("okey\n");
			}
			token_node_free(&shell->token);
		}
		else
			printf("token_NULL\n");
		free(shell->buffer);
		shell->buffer = NULL;
	}
	token_node_free(&shell->token);
	free_env(shell->env_list);
	// free(shell);
	return (0);
}
