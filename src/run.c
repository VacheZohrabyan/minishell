#include "../inc/include.h"

void	run(t_shell *shell)
{
	if (!check_builtin(shell))
		gnacinq(shell);
}