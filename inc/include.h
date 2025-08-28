/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:12:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 15:10:24 by zaleksan         ###   ########.fr       */
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

void	run(t_shell *shell);
#endif