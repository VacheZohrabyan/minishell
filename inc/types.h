/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:43:16 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/26 17:28:48 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "include.h"

typedef enum e_tokken_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
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
	t_env_node			*env_head;
}						t_env;

typedef struct s_redirect
{
	char				*file_name;
	t_token_type		token_type;
	int					fd;
	int					to;
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
	t_env				*export_list;
	int					history_fd;
	t_token				*token;
	char				*buffer;
	t_command			*command;
	int					cmd_count;
	int					status;
	int					**pipe_fd;
	pid_t				*pids;
	int					flag;
}						t_shell;

#endif