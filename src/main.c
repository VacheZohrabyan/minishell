/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/23 13:26:32 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_node;
	t_token	*token;
	char	*buffer;
	pid_t pid;

	env_node = NULL;
	token = NULL;
	buffer = NULL;
	pid = fork();
	if (argc != 1 || !argv[0])
		return (0);
	init_env(&env_node, env);
	sig();
	while (1)
	{
		if (pid < 0)
		{
			printf("chi exe");
		}
		else if (pid == 0)
		{
			buffer = readline("minishell>"); // PROMPT
			if (!buffer)
			{
				printf("exit\n");
				break ;
			if (syntax(token, env_node))
			{
				printf("okey\n");
			}
			add_history(buffer);
			token = lexical(buffer);
			if (token)
			{
				if (syntax(token, env_node))
				{
					check_builtin(token, env_node);
					printf("okey\n");
				}
				token_node_free(&token);
			}
			else
				printf("token_NULL\n");
			free(buffer);
			buffer = NULL;
		}
		else
		{
			wait(NULL);	
		}
	}
	token_node_free(&token);
	free_env(env_node);
	return (0);
}
}