
#include "../../inc/builtin.h"

int	cmd_env(t_env *env)
{
	size_t		i;
	t_env_node	*current;

	if (!env || !env->buffer_env)
		return (1);
	i = 0;
	while (env->buffer_env[i])
	{
		current = env->buffer_env[i];
		while (current)
		{
			if (current->is_equal && current->value)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
		i++;
	}
	return (0);
}
