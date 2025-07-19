/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:49:09 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/19 14:47:55 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/lexical.h"
#include "../inc/my_signal.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_node;
	t_token	*token;
	char	*buffer;

	if (argc != 1 || !argv[0])
		return (0);
	env_node = NULL;
	buffer = NULL;
	token = NULL;
	init_env(&env_node, env);
	sig();
	while (1)
	{
		buffer = readline("minishell>");
		if (!buffer)
			break ;
		add_history(buffer);
		token = lexical(buffer);
		if (token)
			token_node_free(&token);
		free(buffer);
		buffer = NULL;
	}
	token_node_free(&token);
	free_env(env_node);
}
