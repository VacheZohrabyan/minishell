/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:42:22 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/24 10:44:52 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

void	enable_raw_mode(struct termios *orig_term, struct termios *new_term)
{
	if (tcgetattr(STDIN_FILENO, orig_term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	*new_term = *orig_term;
	new_term->c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, new_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	disable_raw_mode(struct termios *orig_term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, orig_term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}
