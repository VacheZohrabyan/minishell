/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:12:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/22 12:07:42 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include "types.h"
# include "parser.h"
# include "lexical.h"
# include "../libft/libft.h"
# include "my_signal.h"
# include "syntax.h"
# include "builtin.h"
# include "gnacinq.h"

extern int g_exit_status;

void	run(t_shell *shell);

#endif