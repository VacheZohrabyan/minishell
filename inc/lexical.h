/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:53:55 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/19 14:16:47 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_H
# define LEXICAL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "libft.h"
# include "parser.h"

typedef enum e_tokken_type
{
	TOKEN_WORD,				// ls.... file.txt
	TOKEN_OPEN,				// (
	TOKEN_CLOSE,			// )
	TOKEN_PIPE,				// |
	TOKEN_OR,				// ||
	TOKEN_AND,				// &&
	TOKEN_REDIRECT_IN,		// <
	TOKEN_REDIRECT_OUT,		// >
	TOKEN_REDIRECT_APPEND,	// >>
	TOKEN_HEREDOC,			// <<
}	t_token_type;

typedef struct s_token
{
	t_token_type	token_type;
	char			*file_name;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token			*lexical(char *buf);
t_token_type	check_token_type(char *buffer);
t_token			*lexical_push_back(t_token *token, char *buffer);

int				syntax_checker(t_token *token);
int				valid_syntax_pipe_or_and(t_token *token);
int				valid_syntax_breket(t_token *current);
int				check_double_operator(t_token *token,
						t_token_type token_type, const char *str);
char* add_spaces_around_specials(const char* buffer);
int is_special(char c);

void			token_node_free(t_token **token);

#endif