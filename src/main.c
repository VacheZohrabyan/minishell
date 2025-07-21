/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 18:21:57 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_node = NULL;
	t_token	*token = NULL;
	char	*buffer = NULL;
	if (argc != 1 || !argv[0])
		return (0);
	init_env(&env_node, env);
	sig();
	while (1)
	{
		buffer = readline("minishell>"); // PROMPT
		if (!buffer)
			break ;
		add_history(buffer);
		token = lexical(buffer);
		printf("hello\n");
		if (token)
		{
			if (sintax(token))
				printf("okey\n");
			token_node_free(&token);
		}
		else
			printf("token_NULL\n");
		free(buffer);
		buffer = NULL;
	}
	token_node_free(&token);
	free_env(env_node);
	return (0);
}
