#include "../../inc/builtin.h"

int	check_builtin(t_token *token, t_env *env)
{
	if (!ft_strcmp("pwd", token->file_name))
		return (cmd_pwd());
	else if (!ft_strcmp("exit", token->file_name))
		return (cmd_exit(token, env));
	return (0);
}