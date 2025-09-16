/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:26:43 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 17:46:44 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "include.h"

# define MALLOC_ERROR "malloc faild \n"
# define MAX_SIZE_ENV 128

t_shell	*init_shell(char **env);
int		init_env_node_value(t_env_node *tmp, char *env, size_t key_size);
int		init_env_node_member(t_env_node *tmp, char *env);
int		init_env_node_key(t_env_node *tmp, char *env, size_t *key_size);
int		push_back(t_env_node **env_node, char *env);
void	init_env(t_env **env, char **envp);
char	*get_env_param(t_env *env, char *key, int flag);
int		set_env_param(t_env *env, char *key, char *value);
void	free_env(t_env **env);
int		parsing(t_command **command, t_token *token);
int		fill_argv_and_redirects(t_redirect **redirect, char **argv,
			t_token *temp, t_token *token);
void	free_redirect(t_redirect **redirect);
void	free_command(t_command **command);

char	**init_argv(t_redirect **redirect, t_token *end,
			t_token *start, int *flag);
int		push_back_command(t_command **command, t_token *start, t_token *end);
int		parsing(t_command **command, t_token *token);
t_shell	*init_shell(char **env);
t_redirect	*init_new_redirect(t_token **tmp);
int		add_redirect(t_redirect **redirect, t_token **tmp);
int		add_word(char **argv, int i, t_token *tmp);
int		validate_and_count(t_token *start, t_token *end);
int		handle_first_word(char **argv, int i, t_token **tmp, int *count);
int		fill_argv_and_redirects(t_redirect **redirect, char **argv,
			t_token *start, t_token *end);
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