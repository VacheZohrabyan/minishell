/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/08/28 13:08:53 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void free_redirect(t_redirect* redirect)
{
    if (!redirect)
        return;
    t_redirect* tmp;
    while (redirect->next)
    {
        tmp = redirect;
        redirect = redirect->next;
        free(tmp);
        tmp->next = NULL;
        tmp = NULL;
    }
    free(redirect);
    redirect = NULL;
}

void free_command(t_command* command)
{
    if (!command)
        return;
    t_command* tmp;
    while (command->next)
    {
        free_redirect(command->redirect);
        tmp = command;
        command = command->next;
        free(tmp);
        tmp->redirect = NULL;
        tmp->next = NULL;
        tmp = NULL;
    }
    free(command);
    command = NULL;
}