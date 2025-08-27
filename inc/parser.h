/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:26:43 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/27 11:54:48 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "include.h"

# define MALLOC_ERROR "malloc faild \n"
# define MAX_SIZE_ENV 128

typedef struct s_redirect
{
    char* file_name;
    t_token_type token_type;
    struct s_redirect *next;
} t_redirect;

typedef struct s_command
{
    char **argv;
    t_redirect *redirect;
    struct s_command *next;
} t_command;

t_shell	*init_shell(char **env);
int		init_env_node_value(t_env_node *tmp, char *env, size_t key_size);
int		init_env_node_member(t_env_node *tmp, char *env);
int		push_back(t_env_node **env_node, char *env);
int		init_env_array(t_env **env_array);
void	init_env(t_env **env_array, char **env);
void	chlp1(t_token *tmp, int *open, int *flag_open);
void	chlp2(t_token *tmp, int *close, int *flag_close, int *open);
int		check(int open, int close, int flag_open, int flag_close);
int		is_valid_close_breaket(t_token *tmp, int open);

void	free_env_node(t_env_node *node);
void	free_env(t_env *env);
int parsing(t_command** command, t_token* token);

#endif

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