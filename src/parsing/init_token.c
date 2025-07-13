/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:14:30 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/13 15:50:16 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"


void init_token(char* buf)
{
    size_t i = 0;
    char** buffer;

    buffer = ft_split(buf, ' ');
    if (!buf)
        exit(24);
    if (chech_operator(buf) == 1)
    while (buffer[i])
    {
        buffer
    }
}