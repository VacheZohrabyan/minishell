/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:22:04 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 20:03:23 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	chlp1(t_token *token)
{
	if (!check_double_operator(token, TOKEN_PIPE, "|"))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_REDIRECT_APPEND))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_HEREDOC))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_REDIRECT_OUT))
		return (0);
	if (!urish_check_double_operator(token, TOKEN_REDIRECT_IN))
		return (0);
	return (1);
}
