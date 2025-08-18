/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/18 14:13:26 by zaleksan         ###   ########.fr       */
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
		{
			printf("exit\n");
			break ;
		}
		add_history(buffer);
		token = lexical(buffer);
		if (token)
		{
			if (syntax(token))
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
	token_node_free(&token);
	free_env(env_node);
	return (0);
}
