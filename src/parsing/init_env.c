/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:55:16 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/13 17:32:58 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	init_env_node_value(t_env_node *tmp, char *env, size_t key_size)
{
	size_t	value_size;
	size_t	i;

	i = 0;
	value_size = key_size + 1;
	while (env[value_size])
		value_size++;
	tmp->value = (char *)malloc(sizeof(char) * (value_size - key_size) + 1);
	if (!tmp->value)
		return (-1);
	while (env[key_size + 1 + i])
	{
		tmp->value[i] = env[key_size + 1 + i];
		++i;
	}
	tmp->value[i] = '\0';
	tmp->is_equal = 1;
	return (0);
}

int	init_env_node_member(t_env_node *tmp, char *env)
{
	size_t	key_size;
	size_t	i;

	key_size = 0;
	i = 0;
	if (*env == '\0')
	{
		tmp->is_equal = 0;
		return (0);
	}
	while (env[key_size] && env[key_size] != '=')
		++key_size;
	tmp->key = (char *)malloc(sizeof(char) * (key_size + 1));
	if (!tmp->key)
		return (-1);
	while (i < key_size)
	{
		tmp->key[i] = env[i];
		++i;
	}
	tmp->key[i] = '\0';
	return (init_env_node_value(tmp, env, key_size));
}

int	push_back(t_env_node **env_node, char *env)
{
	t_env_node	*tmp;
	t_env_node	*current;

	tmp = (t_env_node *)malloc(sizeof(t_env_node));
	current = *env_node;
	if (!tmp)
		return (-1);
	if (init_env_node_member(tmp, env) == -1)
		return (-1);
	tmp->next = NULL;
	if (!current)
		*env_node = tmp;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = tmp;
	}
	return (0);
}

void	free_env(t_env **env)
{
	t_env_node *curr;
    t_env_node *next;

    if (!*env)
        return;

    curr = (*env)->env_head;
    while (curr)
    {
        next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
	free(*env);
}

void init_env(t_env **env, char **envp)
{
    size_t      i;
    t_env_node  *env_node;
	
    *env = (t_env*)malloc(sizeof(t_env));
    if (!*env)
        return;

    env_node = NULL;
    i = 0;
    while (envp[i])
    {
        if (push_back(&env_node, envp[i]) == -1)
        {
			free_env(env);	
            return;
        }
        i++;
    }

    (*env)->env_head = env_node;
    (*env)->exit_code = 0;
}
