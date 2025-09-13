/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:20 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/13 17:20:02 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

// void	free_redirect(t_redirect **redirect)
// {
// 	t_redirect	*tmp;

// 	if (!redirect || !*redirect)
// 		return ;
// 	while ((*redirect))
// 	{
// 		tmp = (*redirect);
// 		(*redirect) = (*redirect)->next;
// 		if ((tmp->file_name))
// 		{
// 			free(tmp->file_name);
// 			tmp->file_name = NULL;
// 		}
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	(*redirect) = NULL;
// }

// void	free_command(t_command **command)
// {
// 	int i;
// 	if (!command || !*command)
// 		return ;
// 	t_command *tmp;
// 	while ((*command))
// 	{
// 		free_redirect(&((*command)->redirect));
// 		tmp = (*command);
// 		(*command) = (*command)->next;
// 		if (tmp->argv)
// 		{
// 			i = 0;
// 			while (tmp->argv[i])
// 			{
// 				free(tmp->argv[i]);
// 				tmp->argv[i] = NULL;
// 				++i;
// 			}
// 			free(tmp->argv);
// 		}
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	(*command) = NULL;
// }

void free_redirect(t_redirect **redirect)
{
    t_redirect *tmp;

    if (!redirect || !*redirect)
        return;
    while (*redirect)
    {
        tmp = *redirect;
        *redirect = tmp->next;
        free(tmp->file_name); // safe even if NULL
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

        // free redirections
        free_redirect(&tmp->redirect);

        // free argv
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
