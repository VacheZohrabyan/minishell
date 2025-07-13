/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:03:43 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/13 15:07:59 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void free_init_env(t_env* str_env)
{
    free(str_env);
    str_env = NULL;
    MALLOC_ERROR("str_env");
    exit(EXIT_FAILURE);
}

void free_init_str_env(t_env* str_env)
{
    size_t i = 0;
    while ((str_env)->env[i])
    {
        free((str_env)->env[i]);
        str_env->env[i++] = NULL;
    }
    free((str_env)->env);
    (str_env)->env = NULL;
    free_init_env(str_env);
}