/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:42:22 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/27 11:51:05 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

void	enable_raw_mode(struct termios *orig_term, struct termios *new_term)
{
	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, orig_term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	*new_term = *orig_term;
	new_term->c_lflag &= ~(0001000);
	if (tcsetattr(STDIN_FILENO, TCSANOW, new_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	disable_raw_mode(struct termios *orig_term)
{
	if (!isatty(STDIN_FILENO))
		return ;
	if (tcsetattr(STDIN_FILENO, TCSANOW, orig_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	main_ctrl_d_body(t_shell *shell)
{
	printf("exit\n");
	close_shell_history(shell);
	free_shell(shell);
	g_exit_status = 130;
	exit(130);
}
