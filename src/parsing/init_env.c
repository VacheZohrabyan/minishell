/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:55:16 by vzohraby          #+#    #+#             */
/*   Updated: 2025/07/15 15:47:39 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int init_env_node_member(t_env_node* tmp, char* env)
{
	size_t key_size = 0;
	size_t value_size = 0;
	size_t i = 0;

	if (*env != '\0')
	{
		while (env[key_size] != '=')
			++key_size;
		tmp->key = (char*)malloc(sizeof(char) * (key_size + 1));
		if (!(tmp->key))
		{
			MALLOC_ERROR("(init_env_node_member)->(tmp->key)");
			return (-1);
		}

		while(env[i] != '=')
		{
			tmp->key[i] = env[i]; 
			++i;
		}
		tmp->key[i] = '\0';
		value_size = key_size + 1;
		while (env[value_size])
			value_size++;
		tmp->value = (char*)malloc(sizeof(char) * (value_size + 1));
		if (!(tmp->value))
		{
			MALLOC_ERROR("(init_env_node_member)->(tmp->value)");
			return (-1);
		}
		i = 0;
		while (env[key_size + 1 + i])
		{
			tmp->value[i] = env[key_size + 1 + i];
			++i;
		}
		tmp->value[i] = '\0';
		tmp->is_equal = 1;
		return (0);
	}
	tmp->is_equal = 0;
	return (0);
}

int push_back(t_env_node** env_node, char* env)
{
	t_env_node* tmp = (t_env_node*)malloc(sizeof(t_env_node));
	t_env_node* current = *env_node;
	if (!tmp)
	{
		MALLOC_ERROR("(push back)->(tmp)");
		return (-1);    
	}
	if (init_env_node_member(tmp, env) == -1)
	{
		MALLOC_ERROR("init_env_node_member");
		return (-1);
	}
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

void init_env(t_env** env_array, char** env)
{
	size_t i = 0;
	t_env_node* env_node = NULL;
	while (env[i])
	{
		if (push_back(&env_node, env[i++]) == -1)
		{
			MALLOC_ERROR("push_back");
			free_env(*env_array);
		}
	}
	i = 0;
	if (!*env_array)
	{
		(*env_array) = (t_env*)malloc(sizeof(t_env));
		if (!(*env_array))
		{
			MALLOC_ERROR("(init_env)->(env_array)");
			free_env(*env_array);
		}
		(*env_array)->buffer_env = (t_env_node**)malloc(sizeof(t_env_node*) * MAX_SIZE_ENV);
		if (!(*env_array)->buffer_env)
		{
			MALLOC_ERROR("(init_env)->(*env_array)->(buffer_env)");
			free_env(*env_array);
		}
		i = 0;
		while (i < MAX_SIZE_ENV)
		{
			(*env_array)->buffer_env[i] = NULL;
			++i;
		}
		(*env_array)->buffer_env[0] = env_node;
		return;
	}
	while ((*env_array)->buffer_env[i])
		++i;

	if (i < MAX_SIZE_ENV)
		(*env_array)->buffer_env[i] = env_node;
	else 
	{
		MALLOC_ERROR("no space ->(init env)");
		free_env(*env_array);
	}
}