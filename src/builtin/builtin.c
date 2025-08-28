/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:05 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 15:25:54 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!ft_strcmp("pwd", shell->token->cmd))
		return (cmd_pwd());
	else if (!ft_strcmp("exit", shell->token->cmd))
		return (cmd_exit(shell));
	else if (!ft_strcmp("env", shell->token->cmd))
		return (cmd_env(shell->env_list));
	return (0);
}
