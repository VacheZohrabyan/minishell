/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:26:43 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/13 14:41:54 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define ENV_LINE_SIZE 64

#define MALLOC_ERROR(str) printf("no space allocated: %s\n", str)

typedef enum e_token_type
{
    TOKEN_WORD,//KOMAND OR UXAKI BAR
    TOKEN_PIPE,//|
    TOKEN_DOUBLE_PIPE,//||
    TOKEN_REDIRECT_IN,//<
    TOKEN_REDIRECT_OUT,//>
    TOKEN_REDIRECT_APPEND,//>>
    TOKEN_HEREDOC,//<<
} t_token_type;

typedef struct s_env
{
    char** env;
} t_env;

typedef struct s_command
{
    char* command;
} t_command;

typedef struct s_token
{
    t_token_type type;
    void* left; //cast mer uzac structov
    void* right; //cast mer uzac structov
} t_token;

t_env* init_env(char** env);

void free_init_env(t_env* str_env);
void free_init_str_env(t_env* str_env);

#endif