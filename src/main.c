/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:49:09 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 18:17:02 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_node;

	if (argc != 1 || !argv[0])
		return (0);
	env_node = NULL;
	init_env(&env_node, env);
	free_env(env_node);
}
