/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:38:06 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/13 15:06:01 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_env* init_env(char** env)
{
    t_env* str_env = NULL;
    size_t i = 0;
    size_t j = 0;
    while (env[i])
        ++i;
    str_env = (t_env*)malloc(sizeof(t_env));
    if (!str_env)
        return (free_init_env(str_env), NULL);
    str_env->env = (char**)malloc(sizeof(char*) * (i + 1));
    if (!str_env->env) 
        return (free_init_str_env(str_env), NULL);
    while (env[j])
    {
        str_env->env[j] = ft_strdup(env[j]);
        if (!str_env->env[j])
        {
            str_env->env[j] = NULL;
            free_init_str_env(str_env);
        }
        ++j;
    }
    str_env->env[i] = NULL;
    return str_env;
}