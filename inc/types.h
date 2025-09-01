/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:43:16 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/01 12:44:49 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "include.h"

typedef enum e_tokken_type
{
	TOKEN_WORD,            // ls.... file.txt
	TOKEN_OPEN,            // (
	TOKEN_CLOSE,           // )
	TOKEN_PIPE,            // |
	TOKEN_OR,              // ||
	TOKEN_AND,             // &&
	TOKEN_REDIRECT_IN,     // <
	TOKEN_REDIRECT_OUT,    // >
	TOKEN_REDIRECT_APPEND, // >>
	TOKEN_HEREDOC,         // <<
}						t_token_type;

typedef struct s_token
{
	t_token_type		token_type;
	char				*cmd;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_ast
{
	char				*operator;
	struct s_ast		*next;
}						t_ast;

typedef struct s_env_node
{
	int					is_equal;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_env
{
	t_env_node			**buffer_env;
	int					exit_code;
}						t_env;

typedef struct s_redirect
{
	char				*file_name;
	t_token_type		token_type;
	int					fd;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	char				**argv;
	t_redirect			*redirect;
	struct s_command	*next;
}						t_command;

typedef struct s_shell
{
	char				**env;
	char				*history;
	t_env				*env_list;
	int					history_fd;
	t_token				*token;
	char				*buffer;
	t_command			*command;
}						t_shell;

#endif