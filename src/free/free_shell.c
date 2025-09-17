/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:37:11 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/17 14:49:20 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	free_shell(t_shell *shell)
{
	free_command(&(shell->command));
	token_node_free(&shell->token);
	free_env(&(shell->env_list));
	free_env(&(shell->export_list));
	free(shell->history);
	free(shell);
}
