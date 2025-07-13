/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:51:13 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/13 15:03:28 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

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

typedef enum e_paren_type
{
	PAREN_NONE,    // Default/Not set
	PAREN_OPEN,    // (
	PAREN_CLOSE    // )
} t_paren_type;

// typedef struct s_token
// {
//     char* ;
//     struct s_token* left;
//     struct s_token* right;
// } t_line;

void parsing(char* buffer);

#endif