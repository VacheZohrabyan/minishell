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
}					t_token_type;

typedef struct s_token
{
	t_token_type	token_type;
	char			*file_name;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ast
{
	char			*operator;
	struct s_ast	*next;
}	t_ast;

typedef struct s_env_node
{
	int					is_equal;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node	**buffer_env;
	int 		exit_code;
}	t_env;

typedef struct s_shell
{
	t_env *env;
	t_token	*token;
} t_shell;

#endif