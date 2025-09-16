/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:19:02 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 18:00:49 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "include.h"

// int	syntax(t_shell *shell, t_token *token);
// int	command_word_for_os(t_token **token);
// int	command_token(char *str);
// int	command_word(char *str);
int	check_double_operator(t_token *token, t_token_type token_type,
		const char *str);
int	urish_check_double_operator(t_token *token, t_token_type token_type);
int	chlp1(t_token *token);
int	ft_strcmp(const char *s1, const char *s2);

#endif