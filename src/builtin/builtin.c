#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!ft_strcmp("pwd", shell->token->cmd))
		return (cmd_pwd());
	else if (!ft_strcmp("exit", shell->token->cmd))
		return (cmd_exit(shell));
	return (0);
}