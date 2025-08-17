/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:21:40 by zaleksan          #+#    #+#             */
/*   Updated: 2025/08/17 15:23:19 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_node;
	t_token	*token;
	char	*buffer;

	env_node = NULL;
	token = NULL;
	buffer = NULL;
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
			if (syntax(token))
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
