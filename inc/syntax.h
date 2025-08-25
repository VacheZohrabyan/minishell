/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:19:02 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/24 12:58:00 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "include.h"

int	syntax(t_shell *shell, t_token *token);
int	command_word_for_os(t_token **token);
int	command_token(char *str);
int	command_word(char *str);
int	ft_strcmp(const char *s1, const char *s2);

#endif