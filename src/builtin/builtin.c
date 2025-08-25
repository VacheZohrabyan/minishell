#include "../../inc/builtin.h"

int	check_builtin(t_shell *shell)
{
	if (!ft_strncmp("pwd", shell->token->cmd, ft_strlen(shell->token->cmd)))
		return (cmd_pwd());
	else if (!ft_strncmp("exit", shell->token->cmd, ft_strlen(shell->token->cmd)))
		return (cmd_exit(shell));
	return (0);
}