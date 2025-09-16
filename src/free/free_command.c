/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/16 10:10:52 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void free_redirect(t_redirect **redirect)
{
    t_redirect *tmp;

    if (!redirect || !*redirect)
        return;
    while (*redirect)
    {
        tmp = *redirect;
        *redirect = tmp->next;
        free(tmp->file_name);
        free(tmp);
    }
    *redirect = NULL;
}

void free_command(t_command **command)
{
    if (!command || !*command)
        return;

    t_command *tmp;
    int i;
    while (*command)
    {
        tmp = *command;
        *command = tmp->next;
        free_redirect(&tmp->redirect);
        if (tmp->argv)
        {
            for (i = 0; tmp->argv[i]; i++)
                free(tmp->argv[i]);
            free(tmp->argv);
        }
        free(tmp);
    }
    *command = NULL;
}
