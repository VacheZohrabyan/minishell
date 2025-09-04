#include "../inc/include.h"

// int	only_builtin(t_shell *shell)
// {
	
// }

void	run(t_shell *shell)
{
	if (!check_builtin(shell, shell->command))
		gnacinq(shell);
}