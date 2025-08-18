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

#endif