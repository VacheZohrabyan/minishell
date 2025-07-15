/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:26:43 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 15:40:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define MALLOC_ERROR(str) printf("malloc faild %s\n", str);

// typedef enum e_token_type
// {
// 	TOKEN_WORD,       // e.g., "ls", "file.txt", or "echo"
// 	TOKEN_OPERATOR,   // e.g., "&&", "||", "|"
// 	TOKEN_PAREN,      // e.g., "(" or ")"
// 	TOKEN_REDIRECT    // e.g., "<", ">", ">>", "<<"
// } t_token_type;

// typedef enum e_operator_type
// {
// 	OPERATOR_NONE,    // Default/Unknown/Not set
// 	OPERATOR_PIPE,    // |
// 	OPERATOR_OR,      // ||
// 	OPERATOR_AND      // &&
// } t_operator_type;

// typedef enum e_redirection_type
// {
// 	REDIRECT_NONE,     // Default/Not set
// 	REDIRECT_IN,       // <
// 	REDIRECT_OUT,      // >
// 	REDIRECT_APPEND,   // >>
// 	REDIRECT_HEREDOC   // <<
// } t_redirection_type;

// typedef enum e_paren_type
// {
// 	PAREN_NONE,    // Default/Not set
// 	PAREN_OPEN,    // (
// 	PAREN_CLOSE    // )
// } t_paren_type;

// typedef struct s_token
// {
//     char* ;
//     struct s_token* left;
//     struct s_token* right;
// } t_line;

#define MAX_SIZE_ENV 128

typedef struct s_env_node
{
    int is_equal;
    char* key;
    char* value;
    struct s_env_node* next;
} t_env_node;

typedef struct s_env
{
   t_env_node** buffer_env; 
} t_env;


void init_env(t_env** env_array, char** env);
int push_back(t_env_node** env_node, char* env);
int init_env_node_member(t_env_node* tmp, char* env);

void env_free(t_env** env);
void env_node_free(t_env_node** env_node);
void env_node_free_member(t_env_node** tmp);
void free_env_node(t_env_node *node);
void free_env(t_env *env);

#endif