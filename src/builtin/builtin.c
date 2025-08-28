/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/27 13:46:41 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!ft_strncmp("pwd", shell->token->cmd,
			ft_strlen(shell->token->cmd)))
		return (cmd_pwd());
	else if (!ft_strncmp("exit", shell->token->cmd,
			ft_strlen(shell->token->cmd)))
		return (cmd_exit(shell));
	return (0);
}
