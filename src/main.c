/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:49:09 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 16:29:29 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int main(int argc, char** argv, char** env)
{
    if (argc != 1 || !argv[0])
        return (0);
    t_env* env_node;
    env_node = NULL;
    // t_env_node* tmp = NULL;
    init_env(&env_node, env);
    init_env(&env_node, env);
    init_env(&env_node, env);
    init_env(&env_node, env);
    init_env(&env_node, env);
    // size_t i = 0;
    // while (i < 5)
    // {
    //     tmp = env_node->buffer_env[i];
    //     while (tmp)
    //     {
    //         printf("%s=%s\n", tmp->key, tmp->value);
    //         tmp = tmp->next;
    //     }
    //     printf("\n\n\n\n");
    //     ++i;
    // }
    free_env(env_node);

}