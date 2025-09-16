/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:53:55 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 16:07:34 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_H
# define LEXICAL_H

# include "include.h"

t_token			*lexical(t_shell *shell);
t_token_type	check_token_type(char *buffer);
t_token			*lexical_push_back(t_shell* shell, char *buffer);

int				syntax_checker(t_token *token);
int				valid_syntax_pipe_or_and(t_token *token);
int				valid_syntax_breket(t_token *current);
int				check_double_operator(t_token *token, t_token_type token_type,
					const char *str);
int				is_special(char c);

int				is_special(char c);
int				is_double_special(const char *buffer, size_t i);
size_t			handle_double_special(const char *buffer, char *result,
					size_t i, size_t *j);
void			handle_single_special(const char *buffer, char *result,
					size_t i, size_t *j);
int				dispatch_special_handler(const char *buffer, char *result,
					size_t *i, size_t *j);
char			*add_spaces_around_specials(const char *buffer);

void			token_node_free(t_token **token);

char **my_split(const char *s, t_env_node* env, char delim);
char	*extract_quotes(char *res, t_env_node *env);
char	*find_env(char *res, t_env_node *env);
char	*append_and_free(char *acc, char *part);
char	*extract_word_function1(const char **s);
char	*extract_word_function2(const char **s, char delim);
char	*extract_word(const char **ps, char delim);
char	*remove_quotes_function1(const char *str, char *out, char *c, int *i);
char	*remove_quotes_function2(const char *str, char *out, char *c, int *i);
char	*remove_quotes(const char *str);
char	**ft_free(char **res, int size);
char	*expend_env_function1(const char *str, int *i,
	char *out, t_env_node *env);
char	*expand_env(const char *str, t_env_node *env);
void	count_words_function1(const char *s, int *i, char delim);
int	count_words(const char *s, char delim);

// from free folder
void			split_free(char ***buffer);

#endif