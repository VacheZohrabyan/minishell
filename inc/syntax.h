/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:11:37 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/16 13:40:09 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINTAX_H
# define SINTAX_H

# include "include.h"

int		syntax(t_token *token);
int		command_word_for_os(t_token *token);
int		command_token(char *str);
int		command_word(char *str);

#endif