/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/30 13:07:21 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void free_redirect(t_redirect** redirect)
{
    if (!*redirect || !redirect)
        return;
    t_redirect* tmp;
    while ((*redirect))
    {
        tmp = (*redirect);
        (*redirect) = (*redirect)->next;
        if ((tmp->file_name))
        {
            free(tmp->file_name);
            tmp->file_name = NULL;
        }
        free(tmp);
        tmp = NULL;
    }
    (*redirect) = NULL;
}

void free_command(t_command** command)
{
    int i;
    if (!*command || !command)
        return;
    t_command* tmp;
    while ((*command))
    {
        free_redirect(&((*command)->redirect));
        tmp = (*command);
        (*command) = (*command)->next;
        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
            {
                free(tmp->argv[i]);
                tmp->argv[i] = NULL;
                ++i;
            }
            free(tmp->argv);
        }
        free(tmp);
        tmp = NULL;
    }
    (*command) = NULL;
}